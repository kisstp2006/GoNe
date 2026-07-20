#ifndef GONE_CAMERA_H
#define GONE_CAMERA_H

#include "engine.h"

typedef enum CAMERA_MODE {
    CAMERA_FOLLOW,      // követi a játékost (alapértelmezett)
    CAMERA_EDITOR,      // szabad FPS kamera (WASD + egér)
} CAMERA_MODE;

// Létrehoz egy kamerát. Alapértelmezetten követő módban indul.
camera_t camera_create(void);

// Frame-enkénti frissítés. Kezeli a módváltást és a kamera mozgatást.
// - follow módban: a target_pos-t követi
// - editor módban: FPS kamera, WASD + egér, F1-el vált vissza
void camera_update(camera_t *cam, vec3 target_pos);

// Visszaadja az aktuális módot
CAMERA_MODE camera_mode(const camera_t *cam);

#endif
