#include <platform/api.h>
#include <allegro.h>

static int old_backend_init(void) { return allegro_init(); }
static void old_backend_quit(void) { allegro_exit(); }

// MS-DOS doesn't have windows.
static nadia_window_t *old_create_window(const char *title, display_t *area, unsigned int flags)
{ (void) title; (void) area; (void) flags; return NULL; }

static void old_destroy_window(void *handle) { (void) handle; return; }

nadia_backend_t NADIA_BACKEND = {
    .init = old_backend_init,
    .init_timer = NULL,
    .init_video = NULL,
    .init_image = NULL,
    .quit = old_backend_quit
};

nadia_gfxapi_t NADIA_GFX = {
    .load_texture = NULL,
    .create_window = old_create_window,
    .destroy_window = old_destroy_window
};
