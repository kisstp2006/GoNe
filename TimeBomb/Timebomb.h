#ifndef GONE_TIMEBOMB_H
#define GONE_TIMEBOMB_H

#include <stdbool.h>
#include <stddef.h>

typedef enum GoneWeekday
{
    GONE_WEEKDAY_SUNDAY = 0,
    GONE_WEEKDAY_MONDAY,
    GONE_WEEKDAY_TUESDAY,
    GONE_WEEKDAY_WEDNESDAY,
    GONE_WEEKDAY_THURSDAY,
    GONE_WEEKDAY_FRIDAY,
    GONE_WEEKDAY_SATURDAY
} GoneWeekday;

typedef struct GoneDate
{
    int year;
    int month;
    int day;
} GoneDate;

typedef struct GoneDateTime
{
    int year;
    int month;
    int day;

    int hour;
    int minute;
    int second;

    /*
     * Sunday = 0
     * Monday = 1
     * ...
     * Saturday = 6
     */
    GoneWeekday weekday;

    /*
     * 1 to 365, or 366 during a leap year.
     */
    int day_of_year;

    /*
     * ISO-8601 week number: 1 to 53.
     */
    int week_of_year;

    /*
     * Positive when daylight-saving time is active.
     * Zero when inactive.
     * Negative when unavailable.
     */
    int is_daylight_saving_time;
} GoneDateTime;

/*
 * Retrieves the current local date and time.
 *
 * Returns true on success.
 * Returns false if the system time could not be retrieved.
 */
bool gone_get_current_datetime(GoneDateTime* out_datetime);

/*
 * Returns the configured expiration date.
 */
GoneDate gone_get_timebomb_date(void);

/*
 * Returns true while the beta version is still valid.
 *
 * The application remains enabled during the entire expiration day.
 */
bool gone_timebomb_is_enabled(void);

/*
 * Returns true after the beta version has expired.
 */
bool gone_timebomb_is_expired(void);

/*
 * Prints the current local date and time.
 */
void gone_print_current_datetime(void);

/*
 * Returns an English weekday name.
 */
const char* gone_get_weekday_name(GoneWeekday weekday);

/*
 * Returns an English month name.
 */
const char* gone_get_month_name(int month);

bool gone_get_current_datetime_string(
    char* buffer,
    size_t buffer_size
);
#endif