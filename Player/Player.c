/*
 * GoNe - Player module
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

#include "Player.h"

// belső segéd: visszaadja a node-hoz csatolt sprite gyereket
static sprite_t *player_sprite(const node_t *p)
{
    array(obj*)* children = (array(obj*)*)obj_children(p);
    if (children && array_count(*children) > 1)
        return (sprite_t *)(*children)[1];
    return NULL;
}

node_t *player_create(const char *ase_file)
{
    // ---- Node (világ-pozíció) ----
    node_t *n = obj_new(node_t);
    obj_setname(n, "PlayerRoot");
    node_teleport(n, vec3(0, 0, 0));
    node_scale(n, vec3(1, 1, 1));

    // ---- Sprite (vizuál) ----
    sprite_t *s = sprite_new(ase_file,
        (int[6]){0, 0, KEY_A, KEY_D, 0, 0});  // csak A/D (balra/jobbra)
    obj_setname(s, "PlayerSprite");
    s->pos = vec4(0, 0, 0, 0);
    s->sca = vec2(0.5f, 0.5f);

    // ---- Hierarchia: sprite a node gyereke ----
    obj_attach(n, s);

    return n;
}

void player_tick(node_t *p)
{
    if (!p) return;

    // ---- Input: A/D mozgatás a NODE-on keresztül ----
    float vel_x = (float)(input(KEY_D) - input(KEY_A));
    if (vel_x != 0.0f) {
        node_move(p, vec3(vel_x, 0, 0));
    }

    // ---- Sprite pozíció szinkronizálása a node-ról ----
    sprite_t *s = player_sprite(p);
    if (s) {
        vec3 np = node_position(p);
        s->pos = vec4(np.x, np.y, np.z, s->pos.w);

        // Sprite animáció (obj_tick kezeli az input + frame váltást)
        obj_tick(s);
    }
}

void player_draw(node_t *p)
{
    if (!p) return;
    sprite_t *s = player_sprite(p);
    if (s) obj_draw(s);
}

vec3 player_pos(const node_t *p)
{
    return p ? node_position(p) : vec3(0, 0, 0);
}
