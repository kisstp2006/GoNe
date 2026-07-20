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
