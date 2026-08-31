#pragma once

#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <platform/config.h>

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

typedef void *nadia_texture_t;  // Either *SDL_Texture or *BITMAP.
typedef void *nadia_renderer_t; // Either SDL_Renderer or Allegro's "screen".
typedef void *nadia_window_t;   // Either SDL_Window or NULL.

typedef struct
{
    int width, height;
    nadia_texture_t data;
} nadia_framebuffer_t;

typedef struct
{
    nadia_window_t      window;
    nadia_renderer_t    renderer;
    nadia_framebuffer_t framebuffer;
} nadia_graphics_t;

nadia_graphics_t *nadia_graphics_init(config_t *configs);
void nadia_graphics_quit(nadia_graphics_t *ctx);

void nadia_clear_display(nadia_graphics_t *ctx, unsigned int color);
void nadia_graphics_present(nadia_graphics_t *ctx);

#endif
