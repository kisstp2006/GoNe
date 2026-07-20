#include "Camera.h"
#include "Game/GameMode.h"

camera_t camera_create(void)
{
    camera_t cam = camera();
    cam.damping = true;
    return cam;
}

CAMERA_MODE camera_mode(const camera_t *cam)
{
    (void)cam;
    return gamemode_is_editing() ? CAMERA_EDITOR : CAMERA_FOLLOW;
}

void camera_update(camera_t *cam, vec3 target_pos)
{
    if (gamemode_is_playing()) {
        // ---- PLAY mód: kamera követi a játékost ----
        camera_teleport(cam, add3(target_pos, vec3(0, 0, 42)));
        camera_lookat(cam, target_pos);
        window_cursor(1);

    } else {
        // ---- EDITOR mód: szabad FPS kamera ----
        bool active = ui_active() || ui_hover() || gizmo_active()
            ? false
            : input(MOUSE_L) || input(MOUSE_M) || input(MOUSE_R);

        window_cursor(!active);

        if (active) {
            cam->speed = clampf(cam->speed + input_diff(MOUSE_W) / 10, 0.05f, 5.0f);

            vec2 mouse = scale2(
                vec2(input_diff(MOUSE_X), -input_diff(MOUSE_Y)),
                0.2f * active);

            vec3 wasd = scale3(
                vec3(input(KEY_D) - input(KEY_A),
                     input(KEY_E) - (input(KEY_C) || input(KEY_Q)),
                     input(KEY_W) - input(KEY_S)),
                cam->speed);

            camera_moveby(cam, scale3(wasd, window_delta() * 60));
            camera_fps(cam, mouse.x, mouse.y);
        }
    }

    camera_enable(cam);
}
