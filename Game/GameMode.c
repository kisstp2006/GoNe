#include "GameMode.h"
#include "engine.h"

static GAMEMODE g_mode = GAMEMODE_PLAY;

void gamemode_init(void)
{
    g_mode = GAMEMODE_PLAY;
}

void gamemode_update(void)
{
    if (input_down(KEY_F1)) {
        g_mode = (g_mode == GAMEMODE_PLAY) ? GAMEMODE_EDITOR : GAMEMODE_PLAY;

        // Editor módban a játék fusson (kamera WASD-hez kell a delta)
        if (g_mode == GAMEMODE_EDITOR) {
            window_pause(false);
        }
    }
}

GAMEMODE gamemode_current(void)
{
    return g_mode;
}

int gamemode_is_playing(void)
{
    return g_mode == GAMEMODE_PLAY;
}

int gamemode_is_editing(void)
{
    return g_mode == GAMEMODE_EDITOR;
}
