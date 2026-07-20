/*
 * GoNe - Player module (header)
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

#ifndef GONE_PLAYER_H
#define GONE_PLAYER_H

#include "engine.h"

// Létrehozza a játékost a megadott .ase fájllal
sprite_t *player_create(const char *ase_file);

// Tick (input + animáció) — minden frame-ben hívni kell
void player_tick(sprite_t *p);

// Kirajzolás — minden frame-ben hívni kell
void player_draw(sprite_t *p);

// Visszaadja a játékos pozícióját (csak olvasható)
vec3 player_pos(const sprite_t *p);

#endif
