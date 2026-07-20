/*
 * GoNe - <brief description>
 * Copyright (C) 2026  <your name>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "engine.h"
#include "Config/BuildConfig.h"
#if GONE_IS_DEBUG_BUILD
    #include "TimeBomb/Timebomb.h"
#endif
#include "Player/Player.h"
#include <stdio.h>
#include <time.h>

#define SCRIPT(...) #__VA_ARGS__

int main(void)
{
    script_init();
    window_create(75.0, 0);
    window_title("GoNe - Demo");

    /* Font aliases */
    #define FONT_REGULAR   FONT_FACE1
    #define FONT_ITALIC    FONT_FACE2
    #define FONT_BOLD      FONT_FACE3
    #define FONT_JAPANESE  FONT_FACE4
    #define FONT_MONOSPACE FONT_FACE5

    #define FONT_GRAY      FONT_COLOR2
    #define FONT_CYAN      FONT_COLOR6
    #define FONT_LIME      FONT_COLOR4

    #define FONT_LARGEST   FONT_H1
    #define FONT_LARGE     FONT_H2
    #define FONT_MEDIUM    FONT_H3
    #define FONT_NORMAL    FONT_H4
    #define FONT_SMALL     FONT_H5
    #define FONT_TINY      FONT_H6

    font_face(FONT_REGULAR,   "B612-Regular.ttf",       48.0f, FONT_EU | FONT_AR | FONT_RU | FONT_2048);
    font_face(FONT_ITALIC,    "B612-Italic.ttf",        48.0f, FONT_EU | FONT_AR | FONT_RU | FONT_2048);
    font_face(FONT_BOLD,      "B612-Bold.ttf",          48.0f, FONT_EU | FONT_AR | FONT_RU | FONT_2048);
    font_face(FONT_JAPANESE,  "mplus-1p-medium.ttf",    48.0f, FONT_JP | FONT_2048);
    font_face(FONT_MONOSPACE, "B612Mono-Regular.ttf",   24.0f, FONT_EU | FONT_512);

    // ---- 3D kamera ----
    camera_t cam = camera();
    cam.damping = true;        // smooth követés

    // ---- 3D sprite (billboard, mindig a kamera felé néz) ----
    sprite_t *player = player_create("Captain Clown Nose.ase");

    while (window_swap() && !input(KEY_ESC))
    {
        // ---- SPRITE MOZGATÁS + ANIMÁCIÓ ----
        player_tick(player);

        // ---- KAMERA követi a sprite-ot ----
        camera_teleport(&cam, add3(player_pos(player), vec3(0, 0, 42)));
        camera_lookat(&cam, player_pos(player));
        camera_enable(&cam);

        // ---- SPRITE KIRAJZOLÁS ----
        player_draw(player);

        // ---- DEBUG SZÖVEG (csak debug buildben) ----
        if (GONE_IS_DEBUG_BUILD)
        {
            // ---- DEBUG GRID (padlórács) ----
            ddraw_grid(0);
            char datetime_string[32];
            char datetime_message[128];

            font_print("This is a Debug build.\n");
            font_print("Build configuration: " GONE_BUILD_NAME "\n");

#if GONE_IS_DEBUG_BUILD
            if (gone_get_current_datetime_string(datetime_string, sizeof(datetime_string)))
            {
                snprintf(datetime_message, sizeof(datetime_message),
                    "Current date and time: %s\n", datetime_string);
                font_print(datetime_message);
            }
#endif

            // Karakter pozíció kiírása
            char pos_message[128];
            vec3 pos = player_pos(player);
            snprintf(pos_message, sizeof(pos_message),
                "Player position: X=%.1f  Y=%.1f  Z=%.1f\n",
                pos.x, pos.y, pos.z);
            font_print(pos_message);

#if GONE_IS_DEBUG_BUILD
            // Hátralevő napok számolása (csak ha < 10 nap)
            {
                GoneDateTime now;
                GoneDate expiry = gone_get_timebomb_date();

                if (gone_get_current_datetime(&now)) {
                    struct tm now_tm = {0};
                    struct tm expiry_tm = {0};

                    now_tm.tm_year = now.year - 1900;
                    now_tm.tm_mon  = now.month - 1;
                    now_tm.tm_mday = now.day;

                    expiry_tm.tm_year = expiry.year - 1900;
                    expiry_tm.tm_mon  = expiry.month - 1;
                    expiry_tm.tm_mday = expiry.day;

                    time_t now_t = mktime(&now_tm);
                    time_t exp_t = mktime(&expiry_tm);

                    if (now_t != (time_t)-1 && exp_t != (time_t)-1) {
                        int days_left = (int)(difftime(exp_t, now_t) / 86400.0);
                        if (days_left >= 0 && days_left <= 10) {
                            char warn[128];
                            snprintf(warn, sizeof(warn),
                                "WARNING: Only %d day(s) until this demo expires!\n",
                                days_left);
                            font_print(warn);
                        }
                    }
                }
            }
#endif

        }
    
    }

    return 0;
}