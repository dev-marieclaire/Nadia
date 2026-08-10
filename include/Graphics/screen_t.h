#pragma once
#include <SDL2/SDL.h>

typedef struct
{
    uint32_t w, h;
    uint32_t x, y;
} screen_t;

extern void clear_screen(SDL_Renderer *renderer, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
extern void present_scene(SDL_Renderer *renderer);
