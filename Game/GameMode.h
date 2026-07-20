#ifndef GONE_GAMEMODE_H
#define GONE_GAMEMODE_H

typedef enum GAMEMODE {
    GAMEMODE_PLAY   = 0,  // játék fut, kamera követ, input aktív
    GAMEMODE_EDITOR = 1,  // szerkesztő mód, szabad FPS kamera, játék pause
} GAMEMODE;

// Kezdő mód: PLAY
void        gamemode_init(void);

// F1-el vált PLAY ↔ EDITOR között. Hívd minden frame elején.
void        gamemode_update(void);

// Visszaadja az aktuális módot
GAMEMODE    gamemode_current(void);

// Kényelmi lekérdezések
int         gamemode_is_playing(void);   // 1 ha PLAY mód
int         gamemode_is_editing(void);   // 1 ha EDITOR mód

#endif
