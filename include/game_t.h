#pragma once
#include <SDL2/SDL.h>

// Struct that defines the highest-level information about the application/game
typedef struct game_t
{
    SDL_Window      *window; // 8 Bytes
    SDL_Renderer    *renderer; // 8 Bytes

    SDL_Rect        rect; // 16 Bytes
    SDL_Event       event; // 56 Bytes

    char            *title;
} game_t;
