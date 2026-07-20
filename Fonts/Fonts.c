#include "Fonts.h"
#include "engine.h"

void fonts_init(void)
{
    font_face(FONT_REGULAR,   "B612-Regular.ttf",       48.0f, FONT_EU | FONT_AR | FONT_RU | FONT_2048);
    font_face(FONT_ITALIC,    "B612-Italic.ttf",        48.0f, FONT_EU | FONT_AR | FONT_RU | FONT_2048);
    font_face(FONT_BOLD,      "B612-Bold.ttf",          48.0f, FONT_EU | FONT_AR | FONT_RU | FONT_2048);
    font_face(FONT_JAPANESE,  "mplus-1p-medium.ttf",    48.0f, FONT_JP | FONT_2048);
    font_face(FONT_MONOSPACE, "B612Mono-Regular.ttf",   24.0f, FONT_EU | FONT_512);
}
