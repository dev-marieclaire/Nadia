// platform/modern/priv_modern.h
#pragma once
#ifndef PRIV_MODERN_H
#define PRIV_MODERN_H

#include <platform/config.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

struct backend_config_t { uint32_t sdl_init_flags; };

struct window_config_t
{
    uint32_t sdl_window_flags;
    int x, y;
};

struct renderer_config_t
{
    uint32_t sdl_renderer_flags;
    int vsync_enabled;
};

struct buffer_config_t
{
    size_t size;
    int unused;
};

struct image_config_t { int img_init_flags; };

/* GRAPHICS */
struct nadia_texture_t { SDL_Texture *texture; };
struct nadia_renderer_t { SDL_Renderer *renderer; };
struct nadia_window_t { SDL_Window *window; };

// ---------------------------
// 3. Input Private Structs (future-proof)
// ---------------------------
// struct nadia_input_t { ... };

#endif // PRIV_MODERN_H
