// platform/modern/config_modern.c
#include "priv_modern.h"
#include <stdlib.h>
#include <string.h>

static config_t* create_default_config(void)
{
    config_t *cfg = malloc(sizeof(config_t));
    if (!cfg) return NULL;

    cfg->logic->backend  = malloc(sizeof(backend_config_t));
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

    // Explicit initialization (malloc does not zero)
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

void free_config(config_t *cfg)
{
    if (!cfg) return;
    free(cfg->logic->backend);
    free(cfg->graphics->window);
    free(cfg->graphics->renderer);
    free(cfg->graphics->buffer);
    free(cfg->graphics->image);
    free(cfg->graphics->display);
    free(cfg->title);
    free(cfg);
}

// ------------------------------------------------------------------
// Global lazy-loaded config
// ------------------------------------------------------------------
static config_t *global_cfg = NULL;

static config_t* ensure_global_cfg(void)
{
    if (!global_cfg) global_cfg = load_default_configs();
    return global_cfg;
}

// --- Struct reference getters ---
static backend_config_t* get_backend(void) {
    config_t *cfg = ensure_global_cfg();
    return cfg ? cfg->logic->backend : NULL;
}

static window_config_t* get_window(void) {
    config_t *cfg = ensure_global_cfg();
    return cfg ? cfg->graphics->window : NULL;
}

static renderer_config_t* get_renderer(void) {
    config_t *cfg = ensure_global_cfg();
    return cfg ? cfg->graphics->renderer : NULL;
}

static buffer_config_t* get_buffer(void) {
    config_t *cfg = ensure_global_cfg();
    return cfg ? cfg->graphics->buffer : NULL;
}

static image_config_t* get_image(void) {
    config_t *cfg = ensure_global_cfg();
    return cfg ? cfg->graphics->image : NULL;
}

static display_t* get_display(void) {
    config_t *cfg = ensure_global_cfg();
    return cfg ? cfg->graphics->display : NULL;
}

static int get_display_w(void)
{
    if (!global_cfg) global_cfg = load_default_configs();
    return global_cfg ? global_cfg->graphics->display->w : 0;
}

static int get_display_h(void)
{
    if (!global_cfg) global_cfg = load_default_configs();
    return global_cfg ? global_cfg->graphics->display->h : 0;
}

static int get_display_x(void)
{
    if (!global_cfg) global_cfg = load_default_configs();
    return global_cfg ? global_cfg->graphics->display->x : 0;
}

static int get_display_y(void)
{
    if (!global_cfg) global_cfg = load_default_configs();
    return global_cfg ? global_cfg->graphics->display->y : 0;
}

static char* get_title(void) {
    if (!global_cfg) global_cfg = load_default_configs();
    return global_cfg ? global_cfg->title : NULL;
}

// --- Scalar flag/value getters ---
static uint32_t get_backend_flags(void) {
    config_t *cfg = ensure_global_cfg();
    return cfg ? cfg->logic->backend->sdl_init_flags : 0;
}

static uint32_t get_window_flags(void) {
    config_t *cfg = ensure_global_cfg();
    return cfg ? cfg->graphics->window->sdl_window_flags : 0;
}

static uint32_t get_renderer_flags(void) {
    config_t *cfg = ensure_global_cfg();
    return cfg ? cfg->graphics->renderer->sdl_renderer_flags : 0;
}

// static size_t get_buffer_flags(void) {
//     config_t *cfg = ensure_global_cfg();
//     return cfg ? cfg->buffer->size : 0;
// }

static int get_image_flags(void) {
    config_t *cfg = ensure_global_cfg();
    return cfg ? cfg->graphics->image->img_init_flags : 0;
}

nadia_config_t NADIA_CONFIG = {
    .configuration = NULL,

    .get_backend       = get_backend,
    .get_window        = get_window,
    .get_renderer      = get_renderer,
    .get_buffer        = get_buffer,
    .get_image         = get_image,

    .get_display       = get_display,
    .get_display_w     = get_display_w,
    .get_display_h     = get_display_h,
    .get_display_x     = get_display_x,
    .get_display_y     = get_display_y,

    .get_title         = get_title,

    .get_backend_flags = get_backend_flags,
    .get_window_flags  = get_window_flags,
    .get_renderer_flags= get_renderer_flags,
    // .get_buffer_flags  = get_buffer_flags,
    .get_image_flags   = get_image_flags,
    .load_defaults     = load_default_configs
};
