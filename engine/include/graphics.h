#pragma once

#ifndef graphics_H
#define graphics_H

#include "graphics/img_t.h"
#include "graphics/sprite_t.h"
#include "graphics/animation_t.h"
#include "graphics/screen_t.h"

#define DEFAULT_SCREEN_WIDTH    320
#define DEFAULT_SCREEN_HEIGHT   200

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

#endif
