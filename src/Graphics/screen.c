// screen.c

#include <SDL2/SDL.h>
// #include <stdio.h>

void clear_screen(SDL_Renderer *renderer, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{   // Sets the background color and clears the screen with that color.
    // Place this before putting any items in screen.

    SDL_SetRenderDrawColor(renderer, r, g, b, a);
    SDL_RenderClear(renderer);
}
