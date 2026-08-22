#pragma once

#ifndef graphics_H
#define graphics_H

#include "graphics/img_t.h"
#include "graphics/sprite_t.h"
#include "graphics/animation_t.h"
#include "graphics/display.h"

#define DEFAULT_DISPLAY_WIDTH    320
#define DEFAULT_DISPLAY_HEIGHT   200

#define DEFAULT_COLOR_DEPTH 8

#ifdef __OLD__
#else
    #include <SDL2/SDL.h>
    #include <SDL2/SDL_image.h>

    // Default flags required in modern systems.
    #define DEFAULT_SDLFLAGS SDL_INIT_VIDEO | SDL_INIT_EVENTS
    #define DEFAULT_WINFLAGS SDL_WINDOW_SHOWN
    #define DEFAULT_FRAMEB_FLAGS SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    #define DEFAULT_IMG_FLAGS IMG_INIT_JPG | IMG_INIT_PNG
#endif

struct framebuffer_t
{
    int     width, height;
    void    *handler;   // Either SDL_Texture or BITMAP.
    void    *render;    // Either SDL_Renderer or Allegro's "screen".
}

struct graphics_t
{
    void    *container; // Either SDL_Window or NULL.
    void    *render_state;
    framebuffer_t   *framebuffer;
};

bool nadia_graphics_init(graphics_t *g, config_t *configs)

#endif
