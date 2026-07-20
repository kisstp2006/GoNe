#ifndef GONE_OUTLINER_H
#define GONE_OUTLINER_H

// Kirajzol egy Godot-stílusú outliner panelt a megfigyelt node-okkal.
// Az editor_frame() UTÁN kell hívni (editor módban).
void outliner_render(void);

// Regisztrál egy node-ot az outlinerbe (és a motor editorába is).
void outliner_watch(void *obj);

#endif
