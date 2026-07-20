/*
 * GoNe - <brief description>
 * Copyright (C) 2026  Kiss Tibor Péter
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
#include "Camera/Camera.h"
#include "Debug/DebugHUD.h"
#include "Fonts/Fonts.h"
#include "Game/GameMode.h"
#include "Player/Player.h"
#include "Scripts/Script.h"

// ---- Játék állapot (statikus, hogy az editor_frame callback elérje) ----
static camera_t  g_cam;
static node_t   *g_player;

// ---- Játék logika (PLAY és EDITOR módban is ez fut) ----
static void game_tick(unsigned frame, float dt, double t)
{
    (void)frame;
    (void)dt;
    (void)t;

    // Inicializálás (első hívásra, frame-től függetlenül)
    static int init_done = 0;
    if (!init_done) {
        init_done = 1;
        g_cam = camera_create();
        g_player = player_create("Captain Clown Nose.ase");
    }

    if (!g_player) return; // még nincs init

    // Tick + kamera + draw
    player_tick(g_player);
    camera_update(&g_cam, player_pos(g_player));
    player_draw(g_player);
    debug_hud_render(player_pos(g_player));
}

int main(void)
{
    script_init();
    scripting_init();
    window_create(75.0, 0);
    window_title("GoNe - Demo");
    fonts_init();
    gamemode_init();

    while (window_swap() && !input(KEY_ESC))
    {
        gamemode_update();

        if (gamemode_is_editing()) {
            // ---- EDITOR mód: editor UI + gizmo + játék ----
            editor_frame(game_tick);
            editor_gizmos(2);
        } else {
            // ---- PLAY mód: játék közvetlenül ----
            game_tick(1, window_delta(), window_time());
        }
    }

    return 0;
}