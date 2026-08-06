#pragma once
#include <SDL2/SDL.h>

// Struct that defines the highest-level information about the application/game
typedef struct game_t
{
    SDL_Window      *window; // 8 Bytes
    unsigned int    win_x, win_y;
    unsigned int    win_w, win_h;
    uint32_t        winflags;
    uint16_t        framerate_target;

    SDL_Renderer    *renderer; // 8 Bytes

    SDL_Rect        rect; // 16 Bytes
    SDL_Event       event; // 56 Bytes

    SDL_Point       center;

    char            *title;
} game_t;
