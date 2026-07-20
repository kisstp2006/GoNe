/*
 * GoNe - Player module
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

#include "Player.h"

sprite_t *player_create(const char *ase_file)
{
    // bindings: {up, down, left, right, action1, action2}
    sprite_t *p = sprite_new(ase_file,
        (int[6]){0, 0, KEY_A, KEY_D, 0, 0});  // csak A/D (balra/jobbra)

    obj_setname(p, "Player");

    // Kezdő pozíció és méret (3D világtérben)
    p->pos = vec4(0, 0, 0, 0);
    p->sca = vec2(0.5f, 0.5f);

    return p;
}

void player_tick(sprite_t *p)
{
    obj_tick(p);
}

void player_draw(sprite_t *p)
{
    obj_draw(p);
}

vec3 player_pos(const sprite_t *p)
{
    return p ? p->pos.xyz : vec3(0, 0, 0);
}
