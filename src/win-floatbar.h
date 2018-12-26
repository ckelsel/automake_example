
#ifndef __WIN_FLOATBAR_H__
#define __WIN_FLOATBAR_H__

#include <windows.h>

#define FLOATBAR_ENABLE 0x0001
#define FLOATBAR_LOCKED 0x0002
#define FLOATBAR_SHOW   0x0004
#define FLOATBAR_SHOW_IN_FULLSCREEN_MODE 0x0010
#define FLOATBAR_SHOW_IN_WINDOWS_MODE    0x0020


typedef struct _FloatBar wfFloatBar;
typedef struct wf_context wfContext;

struct wf_context {
    void *toplevel;
    void *winspice;
    HWND parent;
    BOOL with_minimize;
    BOOL with_ctrlaltdel;
    BOOL fullscreen;
    HINSTANCE hInstance;
    char window_title[32];
};

wfFloatBar* wf_floatbar_new(wfContext* wfc, HINSTANCE window, DWORD flags);
void wf_floatbar_free(wfFloatBar* floatbar);

BOOL wf_floatbar_toggle_fullscreen(wfFloatBar* floatbar, BOOL fullscreen);

#endif // __WIN_FLOATBAR_H__
