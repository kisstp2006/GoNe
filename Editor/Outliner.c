#include "Outliner.h"
#include "engine.h"

#define MAX_ROOTS 64
static void *g_roots[MAX_ROOTS];
static int   g_root_count;

// Track which nodes are expanded in the tree (simple int flag, 1=open)
static int outliner_is_open(void *o) {
    // Use editor's built-in open state (editor_setopen/editor_open)
    return editor_open(o);
}

static void outliner_toggle_open(void *o) {
    editor_setopen(o, !editor_open(o));
}

// Recursively draw a node and its children (based on engine's editor_scene_)
static void outliner_draw_node(void *o, int depth)
{
    if (!o) return;

    const char *name = obj_name(o);
    const char *type = obj_type(o);
    int has_children = array_count(*obj_children(o)) > 1;

    if (!name) name = "(unnamed)";
    if (!type) type = "?";

    // Chevron: expand/collapse indicator
    const char *chevron = !has_children ? "  " :
        outliner_is_open(o) ? ICON_MD_EXPAND_MORE : ICON_MD_CHEVRON_RIGHT;

    // Indentation
    char indent[64] = "";
    int d = depth;
    if (d > 30) d = 30;
    for (int i = 0; i < d; ++i)
        strcat(indent, "  ");

    // Selection highlight
    int selected = editor_selected(o);

    // Label: [>] Name (Type)  (* = selected)
    char label[256];
    snprintf(label, sizeof(label), "%s%s %s (%s)%s",
        indent,
        chevron,
        name, type,
        selected ? "  [*]" : "");

    if (ui_label(label)) {
        // Clicked: toggle open or select
        if (has_children) {
            outliner_toggle_open(o);
        }
    }

    // Recurse into children if expanded
    if (has_children && outliner_is_open(o)) {
        for each_objchild(o, obj*, child) {
            outliner_draw_node(child, depth + 1);
        }
    }
}

void outliner_watch(void *obj)
{
    if (obj && g_root_count < MAX_ROOTS) {
        g_roots[g_root_count++] = obj;
    }
}

void outliner_render(void)
{
    if (ui_panel("Outliner", PANEL_OPEN)) {
        ui_separator();

        if (g_root_count == 0) {
            ui_label("(no nodes in scene)");
        } else {
            for (int i = 0; i < g_root_count; ++i) {
                outliner_draw_node(g_roots[i], 0);
            }
        }

        ui_panel_end();
    }
}


