#ifndef GONE_FONTS_H
#define GONE_FONTS_H

// Betölti a játékhoz szükséges összes fontot.
// Egyszer kell meghívni, a window_create() után.
void fonts_init(void);

// Font aliasok
#define FONT_REGULAR   FONT_FACE1
#define FONT_ITALIC    FONT_FACE2
#define FONT_BOLD      FONT_FACE3
#define FONT_JAPANESE  FONT_FACE4
#define FONT_MONOSPACE FONT_FACE5

#define FONT_GRAY      FONT_COLOR2
#define FONT_CYAN      FONT_COLOR6
#define FONT_LIME      FONT_COLOR4

#define FONT_LARGEST   FONT_H1
#define FONT_LARGE     FONT_H2
#define FONT_MEDIUM    FONT_H3
#define FONT_NORMAL    FONT_H4
#define FONT_SMALL     FONT_H5
#define FONT_TINY      FONT_H6

#endif
