#pragma once

#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <config.h>

#include <graphics/sprite.h>
#include <graphics/animation.h>

#include <display.h>

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
// For this purpose, SDL_Texture and BITMAP * will be casted to nadia_texture_t.
// SDL_Renderer and Allegro's screen will be stored in nadia_renderer_t.
// And, finally, SDL_Window will be stored in nadia_window_t.
typedef struct nadia_texture_t nadia_texture_t;
typedef struct nadia_renderer_t nadia_renderer_t;
typedef struct nadia_window_t nadia_window_t;

typedef struct
{
    // Stores the dimensions of the framebuffer.
    int w, h;

    // Either *SDL_Texture or *BITMAP.
    nadia_texture_t *data;
} nadia_framebuffer_t;

typedef struct
{
    nadia_window_t      *window;    // Either SDL_Window or NULL.
    nadia_renderer_t    *renderer;  // Either SDL_Renderer or Allegro's "screen".
    nadia_framebuffer_t backbuffer; // Either NULL or a BITMAP *backbuffer.
} nadia_graphics_t;

// Initializes the graphical environment.
nadia_graphics_t *nadia_graphics_init(config_t *configs);

// Quits the graphical environment.
void nadia_graphics_quit(nadia_graphics_t *ctx);

// Clears the display to a color.
// The color format must be aRGB, being alpha the first two digits in a hexadecimal
// number in a 32 bit color depth mode.
// If the color mode doesn't support Alpha channel, like in a 24 bit color depth
// mode "True color", the alpha values are just ignored.
void nadia_clear_display(nadia_graphics_t *ctx, unsigned int color);

// Copies the contents of the backbuffer into the framebuffer or renderer.
void nadia_graphics_present(nadia_graphics_t *ctx);

#endif
