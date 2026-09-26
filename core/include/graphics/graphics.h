#pragma once

#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <platform/config.h>

// #include <graphics/sprite.h>
#include <graphics/animation.h>

#define DEFAULT_DISPLAY_WIDTH    320
#define DEFAULT_DISPLAY_HEIGHT   200

#define DEFAULT_COLOR_DEPTH 24

#ifdef __MODERN__
    #include <SDL2/SDL.h>
    #include <SDL2/SDL_image.h>

    // Default flags required in modern systems.
    #define DEFAULT_SDLFLAGS SDL_INIT_VIDEO | SDL_INIT_EVENTS
    #define DEFAULT_WINFLAGS SDL_WINDOW_SHOWN
    #define DEFAULT_FRAMEB_FLAGS SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    #define DEFAULT_IMG_FLAGS IMG_INIT_JPG | IMG_INIT_PNG
#endif

// Opaque definitions for components in a graphical context.
// These definitions serve a single purpose:
// To store a pointer of a single component inside a graphical context.
// Currently, Nadia uses two libraries for supporting modern and arcaic systems.
// But these two libraries do work differently (obviously) and there must be a
// conciliator or mediator.
//
// nadia_texture_t  — GPU-side data. Wraps SDL_Texture or BITMAP *.
// nadia_image_t    — CPU-side pixel buffer. Wraps SDL_Surface *.
// nadia_renderer_t — Wraps SDL_Renderer or Allegro's screen.
// nadia_window_t   — Wraps SDL_Window.
typedef struct nadia_texture_t  nadia_texture_t;
typedef struct nadia_image_t    nadia_image_t;
typedef struct nadia_renderer_t nadia_renderer_t;
typedef struct nadia_window_t   nadia_window_t;

// Descriptor used to configure a new graphical context.
//
// Configuration ownership:
// - When `config` is NULL, the context creates its own private default
//   configuration and takes ownership of it. `take_ownership` is ignored.
// - When `config` is non-NULL, the context uses it. If `take_ownership` is
//   non-zero, the context calls free_config() on it at quit. If zero, the
//   caller remains responsible for freeing it, and the same config can be
//   shared across multiple contexts.
//
// The remaining fields are per-call overrides applied on top of the config.
// Leave them NULL / zero to fall back to the config's values.
typedef struct
{
    config_t    *config;
    int          take_ownership;

    const char  *title;
    display_t   *area;
    unsigned int flags;
} nadia_graphics_context_desc_t;

typedef struct
{
    // The configuration this context reads from.
    config_t            *config;

    // Non-zero when this context owns its config and must free it at quit.
    int                  owns_config;

    // Points at the config's display struct, or NULL if the config has none.
    display_t           *display;

    nadia_window_t      *window;    // Either a wrapped SDL_Window or NULL.
    nadia_renderer_t    *renderer;  // Either a wrapped SDL_Renderer or Allegro's screen.
    nadia_texture_t     *backbuffer; // Either an empty framebuffer or a wrapped BITMAP.
} nadia_graphics_context_t;

typedef struct
{
    // Initializes a new graphical context from the given descriptor.
    // Returns NULL on failure.
    nadia_graphics_context_t *(*create_context)(const nadia_graphics_context_desc_t *desc);

    // Releases all resources held by the given context and frees it.
    // Frees the context's config only if the context owns it.
    void (*quit)(nadia_graphics_context_t *ctx);

    // Clears the given context's display to a color.
    // The color format must be aRGB, being alpha the first two digits in a hexadecimal
    // number in a 32 bit color depth mode.
    // If the color mode doesn't support Alpha channel, like in a 24 bit color depth
    // mode "True color", the alpha values are just ignored.
    void (*clear_display)(nadia_graphics_context_t *ctx, unsigned int color);

    // Copies the contents of the backbuffer into the framebuffer or renderer.
    void (*present)(nadia_graphics_context_t *ctx);

    // Loads a texture into the given renderer.
    nadia_texture_t *(*load_texture)(const char *src, nadia_renderer_t *dest);

    // Releases a texture previously created by load_texture.
    void (*free_texture)(nadia_texture_t *texture);

    // Creates a window using the given config for defaults.
    // Fields in `area` and `flags` that are zero fall back to the config.
    // Used internally by create_context, but exposed for backends that may
    // want to manage windows independently.
    nadia_window_t *(*create_window)(
        const config_t *cfg,
        const char *title,
        display_t *area,
        unsigned int flags
    );

    // Destroys a window previously created by create_window.
    void (*destroy_window)(nadia_window_t *instance);
} nadia_graphics_backend_t;

typedef struct
{
    const nadia_graphics_backend_t *backend;
    nadia_graphics_context_t      **instances;
    int                             size;
    int                             capacity;
} nadia_graphics_t;

extern nadia_graphics_t NADIA_GRAPHICS;

/* PUBLIC API */

// Resolves an index to a graphical context, or NULL if the index is invalid
// or refers to a hole left by a destroyed context.
nadia_graphics_context_t *nadia_graphics_resolve(int index);

// Creates a new graphical context and returns its index.
// Returns -1 on failure.
// See nadia_graphics_context_desc_t for config ownership rules.
int nadia_graphics_create_context(const nadia_graphics_context_desc_t *desc);

// Destroys the context at the given index, leaving a reusable hole.
void nadia_graphics_quit_context(int index);

// Clears the given context's display to a color.
void nadia_graphics_clear_display(int index, unsigned int color);

// Presents the given context.
void nadia_graphics_present(int index);

// Loads a texture for the given context.
nadia_texture_t *nadia_graphics_load_texture(int index, const char *src);

// Releases a texture previously created by nadia_graphics_load_texture.
void nadia_graphics_free_texture(nadia_texture_t *texture);

#endif
