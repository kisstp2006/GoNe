#include "Timebomb.h"

#include <stdio.h>
#include <time.h>

/*
 * Set this to 0 for release builds that must never expire.
 *
 * It can also be defined from the build system:
 *
 *     -DGONE_TIMEBOMB_ENABLED=1
 */
#ifndef GONE_TIMEBOMB_ENABLED
    #define GONE_TIMEBOMB_ENABLED 1
#endif

/*
 * Beta expiration date.
 *
 * With this configuration, the application still runs on
 * August 31, 2026, but no longer runs from September 1, 2026.
 */
#ifndef GONE_TIMEBOMB_YEAR
    #define GONE_TIMEBOMB_YEAR 2026
#endif

#ifndef GONE_TIMEBOMB_MONTH
    #define GONE_TIMEBOMB_MONTH 8
#endif

#ifndef GONE_TIMEBOMB_DAY
    #define GONE_TIMEBOMB_DAY 31
#endif

static const char* GONE_WEEKDAY_NAMES[7] =
{
    "Sunday",
    "Monday",
    "Tuesday",
    "Wednesday",
    "Thursday",
    "Friday",
    "Saturday"
};

static const char* GONE_MONTH_NAMES[12] =
{
    "January",
    "February",
    "March",
    "April",
    "May",
    "June",
    "July",
    "August",
    "September",
    "October",
    "November",
    "December"
};

static bool gone_is_leap_year(int year)
{
    if (year % 400 == 0)
    {
        return true;
    }

    if (year % 100 == 0)
    {
        return false;
    }

    return year % 4 == 0;
}

static int gone_get_days_in_month(int year, int month)
{
    static const int days_per_month[12] =
    {
        31, 28, 31, 30,
        31, 30, 31, 31,
        30, 31, 30, 31
    };

    if (month < 1 || month > 12)
    {
        return 0;
    }

    if (month == 2 && gone_is_leap_year(year))
    {
        return 29;
    }

    return days_per_month[month - 1];
}

static bool gone_is_valid_date(const GoneDate* date)
{
    int days_in_month;

    if (date == NULL)
    {
        return false;
    }

    if (date->year < 1970)
    {
        return false;
    }

    if (date->month < 1 || date->month > 12)
    {
        return false;
    }

    days_in_month = gone_get_days_in_month(
        date->year,
        date->month
    );

    if (date->day < 1 || date->day > days_in_month)
    {
        return false;
    }

    return true;
}

static int gone_date_to_number(const GoneDate* date)
{
    /*
     * Converts:
     *
     *     2026-08-31
     *
     * into:
     *
     *     20260831
     *
     * This makes dates easy to compare.
     */
    return
        date->year * 10000 +
        date->month * 100 +
        date->day;
}

static int gone_calculate_weekday(
    int year,
    int month,
    int day
)
{
    /*
     * Returns:
     *
     * 0 = Sunday
     * 1 = Monday
     * ...
     * 6 = Saturday
     */
    static const int month_offsets[12] =
    {
        0, 3, 2, 5,
        0, 3, 5, 1,
        4, 6, 2, 4
    };

    if (month < 3)
    {
        year -= 1;
    }

    return
        (
            year +
            year / 4 -
            year / 100 +
            year / 400 +
            month_offsets[month - 1] +
            day
        ) % 7;
}

static int gone_get_iso_weeks_in_year(int year)
{
    int january_first_weekday;

    january_first_weekday =
        gone_calculate_weekday(year, 1, 1);

    /*
     * Convert:
     *
     * Sunday = 0, Monday = 1, ...
     *
     * into ISO format:
     *
     * Monday = 1, ..., Sunday = 7
     */
    if (january_first_weekday == 0)
    {
        january_first_weekday = 7;
    }

    /*
     * An ISO year has 53 weeks when:
     *
     * - January 1 is Thursday, or
     * - January 1 is Wednesday during a leap year.
     */
    if (january_first_weekday == 4)
    {
        return 53;
    }

    if (
        january_first_weekday == 3 &&
        gone_is_leap_year(year)
    )
    {
        return 53;
    }

    return 52;
}

static int gone_calculate_iso_week(
    int year,
    int day_of_year,
    GoneWeekday weekday
)
{
    int iso_weekday;
    int week;

    /*
     * Convert Sunday from 0 to ISO weekday 7.
     */
    iso_weekday =
        weekday == GONE_WEEKDAY_SUNDAY
            ? 7
            : (int)weekday;

    week =
        (
            day_of_year -
            iso_weekday +
            10
        ) / 7;

    if (week < 1)
    {
        return gone_get_iso_weeks_in_year(year - 1);
    }

    if (week > gone_get_iso_weeks_in_year(year))
    {
        return 1;
    }

    return week;
}

static bool gone_get_local_time(
    time_t current_time,
    struct tm* out_local_time
)
{
    if (out_local_time == NULL)
    {
        return false;
    }

#if defined(_WIN32)

    /*
     * Microsoft C runtime.
     */
    return localtime_s(
        out_local_time,
        &current_time
    ) == 0;

#elif defined(__unix__) || defined(__APPLE__)

    /*
     * Linux, macOS and other POSIX systems.
     */
    return localtime_r(
        &current_time,
        out_local_time
    ) != NULL;

#else

    /*
     * Standard C fallback.
     *
     * localtime() uses internal shared storage, so this fallback
     * is not thread-safe during the call.
     */
    {
        struct tm* temporary_time;

        temporary_time = localtime(&current_time);

        if (temporary_time == NULL)
        {
            return false;
        }

        *out_local_time = *temporary_time;
        return true;
    }

#endif
}

bool gone_get_current_datetime(GoneDateTime* out_datetime)
{
    time_t current_time;
    struct tm local_time;

    if (out_datetime == NULL)
    {
        return false;
    }

    current_time = time(NULL);

    if (current_time == (time_t)-1)
    {
        return false;
    }

    if (!gone_get_local_time(current_time, &local_time))
    {
        return false;
    }

    out_datetime->year =
        local_time.tm_year + 1900;

    out_datetime->month =
        local_time.tm_mon + 1;

    out_datetime->day =
        local_time.tm_mday;

    out_datetime->hour =
        local_time.tm_hour;

    out_datetime->minute =
        local_time.tm_min;

    out_datetime->second =
        local_time.tm_sec;

    out_datetime->weekday =
        (GoneWeekday)local_time.tm_wday;

    out_datetime->day_of_year =
        local_time.tm_yday + 1;

    out_datetime->week_of_year =
        gone_calculate_iso_week(
            out_datetime->year,
            out_datetime->day_of_year,
            out_datetime->weekday
        );

    out_datetime->is_daylight_saving_time =
        local_time.tm_isdst;

    return true;
}

GoneDate gone_get_timebomb_date(void)
{
    GoneDate expiration_date;

    expiration_date.year =
        GONE_TIMEBOMB_YEAR;

    expiration_date.month =
        GONE_TIMEBOMB_MONTH;

    expiration_date.day =
        GONE_TIMEBOMB_DAY;

    return expiration_date;
}

bool gone_timebomb_is_enabled(void)
{
#if GONE_TIMEBOMB_ENABLED == 0

    /*
     * Timebomb disabled, usually for a full release build.
     */
    return true;

#else

    GoneDateTime current_datetime;
    GoneDate current_date;
    GoneDate expiration_date;

    if (!gone_get_current_datetime(&current_datetime))
    {
        /*
         * Fail closed when the system time cannot be retrieved.
         */
        return false;
    }

    current_date.year =
        current_datetime.year;

    current_date.month =
        current_datetime.month;

    current_date.day =
        current_datetime.day;

    expiration_date =
        gone_get_timebomb_date();

    if (!gone_is_valid_date(&current_date))
    {
        return false;
    }

    if (!gone_is_valid_date(&expiration_date))
    {
        return false;
    }

    /*
     * <= means the application remains usable for the entire
     * expiration day.
     */
    return
        gone_date_to_number(&current_date) <=
        gone_date_to_number(&expiration_date);

#endif
}

bool gone_timebomb_is_expired(void)
{
    return !gone_timebomb_is_enabled();
}

const char* gone_get_weekday_name(GoneWeekday weekday)
{
    if (
        weekday < GONE_WEEKDAY_SUNDAY ||
        weekday > GONE_WEEKDAY_SATURDAY
    )
    {
        return "Unknown";
    }

    return GONE_WEEKDAY_NAMES[(int)weekday];
}

const char* gone_get_month_name(int month)
{
    if (month < 1 || month > 12)
    {
        return "Unknown";
    }

    return GONE_MONTH_NAMES[month - 1];
}

void gone_print_current_datetime(void)
{
    GoneDateTime datetime;

    if (!gone_get_current_datetime(&datetime))
    {
        fprintf(
            stderr,
            "Failed to retrieve the current date and time.\n"
        );

        return;
    }

    printf(
        "Current date and time: "
        "%04d-%02d-%02d %02d:%02d:%02d\n",
        datetime.year,
        datetime.month,
        datetime.day,
        datetime.hour,
        datetime.minute,
        datetime.second
    );

    printf(
        "Formatted date: %s, %s %d, %d\n",
        gone_get_weekday_name(datetime.weekday),
        gone_get_month_name(datetime.month),
        datetime.day,
        datetime.year
    );

    printf(
        "Time: %02d:%02d:%02d\n",
        datetime.hour,
        datetime.minute,
        datetime.second
    );

    printf(
        "Day of year: %d\n",
        datetime.day_of_year
    );

    printf(
        "ISO week of year: %d\n",
        datetime.week_of_year
    );

    if (datetime.is_daylight_saving_time > 0)
    {
        printf("Daylight-saving time: active\n");
    }
    else if (datetime.is_daylight_saving_time == 0)
    {
        printf("Daylight-saving time: inactive\n");
    }
    else
    {
        printf("Daylight-saving time: unknown\n");
    }
}

bool gone_get_current_datetime_string(
    char* buffer,
    size_t buffer_size
)
{
    GoneDateTime datetime;
    int written;

    if (buffer == NULL || buffer_size == 0)
    {
        return false;
    }

    /*
     * Always produce an empty string on failure.
     */
    buffer[0] = '\0';

    if (!gone_get_current_datetime(&datetime))
    {
        return false;
    }

    written = snprintf(
        buffer,
        buffer_size,
        "%04d-%02d-%02d %02d:%02d:%02d",
        datetime.year,
        datetime.month,
        datetime.day,
        datetime.hour,
        datetime.minute,
        datetime.second
    );

    if (written < 0)
    {
        buffer[0] = '\0';
        return false;
    }

    if ((size_t)written >= buffer_size)
    {
        /*
         * The buffer was too small.
         */
        buffer[0] = '\0';
        return false;
    }

    return true;
}