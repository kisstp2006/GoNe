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
