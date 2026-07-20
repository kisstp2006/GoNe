#include "Script.h"
#include "engine.h"

void scripting_init(void)
{
    // Teal compiler + .tl fájlok require() támogatása
    script_run("require('tl').loader()");

    // Belépőponti script futtatása (ha létezik)
    if (vfs_handle("Scripts/ui_demo.lua"))
        script_runfile("Scripts/ui_demo.lua");
}
