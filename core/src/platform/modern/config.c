// platform/modern/config_modern.c
#include "priv_modern.h"
#include <stdlib.h>
#include <string.h>

static config_t* create_default_config(void)
{
    config_t *cfg = malloc(sizeof(config_t));
    if (!cfg) return NULL;

    // Zero-fill so free_config can safely clean up a half-built config.
    memset(cfg, 0, sizeof(*cfg));

    // Allocates the two container structs first, since every sub-config
    // below hangs off of them.
    cfg->logic    = malloc(sizeof(logical_config_t));
    cfg->graphics = malloc(sizeof(graphics_config_t));

    if (!cfg->logic || !cfg->graphics) {
        free_config(cfg);
        return NULL;
    }

    memset(cfg->logic,    0, sizeof(*cfg->logic));
    memset(cfg->graphics, 0, sizeof(*cfg->graphics));

    // Allocates the opaque sub-configs.
    cfg->logic->backend     = malloc(sizeof(backend_config_t));
    cfg->graphics->window   = malloc(sizeof(window_config_t));
    cfg->graphics->renderer = malloc(sizeof(renderer_config_t));
    cfg->graphics->buffer   = malloc(sizeof(buffer_config_t));
    cfg->graphics->image    = malloc(sizeof(image_config_t));
    cfg->graphics->display  = malloc(sizeof(display_t));

    if (!cfg->logic->backend || !cfg->graphics->window || !cfg->graphics->renderer ||
        !cfg->graphics->buffer || !cfg->graphics->image || !cfg->graphics->display) {
        free_config(cfg);
        return NULL;
    }

    // Explicit initialization (malloc does not zero).
    cfg->title = NULL;

    cfg->logic->backend->sdl_init_flags = SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_TIMER;

    cfg->graphics->window->sdl_window_flags = SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE;
    cfg->graphics->window->x = SDL_WINDOWPOS_CENTERED;
    cfg->graphics->window->y = SDL_WINDOWPOS_CENTERED;

    cfg->graphics->renderer->sdl_renderer_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
    cfg->graphics->renderer->vsync_enabled = 1;

    cfg->graphics->buffer->size   = 0;
    cfg->graphics->buffer->unused = 0;

    cfg->graphics->image->img_init_flags = IMG_INIT_PNG | IMG_INIT_JPG;

    cfg->graphics->display->x = -1;
    cfg->graphics->display->y = -1;
    cfg->graphics->display->w = 800;
    cfg->graphics->display->h = 600;

    cfg->title = strdup("APPLICATION");
    if (!cfg->title) {
        free_config(cfg);
        return NULL;
    }

    return cfg;
}

config_t *load_default_configs(void) { return create_default_config(); }

// Frees every sub-config, then the containers, then the config itself.
// Null-safe at every level so it can be used on partially-built configs.
void free_config(config_t *cfg)
{
    if (!cfg) return;

    if (cfg->logic) {
        free(cfg->logic->backend);
        free(cfg->logic);
    }
    if (cfg->graphics) {
        free(cfg->graphics->window);
        free(cfg->graphics->renderer);
        free(cfg->graphics->buffer);
        free(cfg->graphics->image);
        free(cfg->graphics->display);
        free(cfg->graphics);
    }
    free(cfg->title);
    free(cfg);
}

// ------------------------------------------------------------------
// Global lazy-loaded default configuration
// The library owns this instance; callers must not free it.
// ------------------------------------------------------------------
static config_t *global_cfg = NULL;

static config_t* default_config(void)
{
    if (!global_cfg) global_cfg = load_default_configs();
    return global_cfg;
}

// --- Struct reference getters ---
static backend_config_t* get_backend(const config_t *cfg) {
    return (cfg && cfg->logic) ? cfg->logic->backend : NULL;
}

static window_config_t* get_window(const config_t *cfg) {
    return (cfg && cfg->graphics) ? cfg->graphics->window : NULL;
}

static renderer_config_t* get_renderer(const config_t *cfg) {
    return (cfg && cfg->graphics) ? cfg->graphics->renderer : NULL;
}

static buffer_config_t* get_buffer(const config_t *cfg) {
    return (cfg && cfg->graphics) ? cfg->graphics->buffer : NULL;
}

static image_config_t* get_image(const config_t *cfg) {
    return (cfg && cfg->graphics) ? cfg->graphics->image : NULL;
}

static display_t* get_display(const config_t *cfg) {
    return (cfg && cfg->graphics) ? cfg->graphics->display : NULL;
}

// --- Scalar getters (delegate to the reference getters) ---
static int get_display_w(const config_t *cfg)
{
    display_t *d = get_display(cfg);
    return d ? (int) d->w : 0;
}

static int get_display_h(const config_t *cfg)
{
    display_t *d = get_display(cfg);
    return d ? (int) d->h : 0;
}

static int get_display_x(const config_t *cfg)
{
    display_t *d = get_display(cfg);
    return d ? d->x : 0;
}

static int get_display_y(const config_t *cfg)
{
    display_t *d = get_display(cfg);
    return d ? d->y : 0;
}

static char* get_title(const config_t *cfg) {
    return cfg ? cfg->title : NULL;
}

static int get_backend_flags(const config_t *cfg) {
    backend_config_t *b = get_backend(cfg);
    return b ? b->sdl_init_flags : 0;
}

static int get_window_flags(const config_t *cfg) {
    window_config_t *w = get_window(cfg);
    return w ? w->sdl_window_flags : 0;
}

static int get_renderer_flags(const config_t *cfg) {
    renderer_config_t *r = get_renderer(cfg);
    return r ? r->sdl_renderer_flags : 0;
}

// static size_t get_buffer_flags(const config_t *cfg) {
//     buffer_config_t *b = get_buffer(cfg);
//     return b ? b->size : 0;
// }

static int get_image_flags(const config_t *cfg) {
    image_config_t *i = get_image(cfg);
    return i ? i->img_init_flags : 0;
}

nadia_config_t NADIA_CONFIG = {
    .default_config     = default_config,

    .get_backend        = get_backend,
    .get_window         = get_window,
    .get_renderer       = get_renderer,
    .get_buffer         = get_buffer,
    .get_image          = get_image,

    .get_display        = get_display,
    .get_display_w      = get_display_w,
    .get_display_h      = get_display_h,
    .get_display_x      = get_display_x,
    .get_display_y      = get_display_y,

    .get_title          = get_title,

    .get_backend_flags  = get_backend_flags,
    .get_window_flags   = get_window_flags,
    .get_renderer_flags = get_renderer_flags,
    // .get_buffer_flags   = get_buffer_flags,
    .get_image_flags    = get_image_flags,

    .load_defaults      = load_default_configs
};
