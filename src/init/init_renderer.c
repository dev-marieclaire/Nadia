// init_renderer.c

#ifdef __DJGPP__

#else

#include <SDL2/SDL.h>

#include "defaults.h"

// Initializes a renderer with custom values and performs a checking
SDL_Renderer *create_custom_renderer(SDL_Window *win, int index, int flags)
{
    int _flags = flags;
    if (!_flags) _flags = DEFAULT_REND_FLAGS;

    SDL_Renderer *r = SDL_CreateRenderer(win, index, flags);

    if (!r)
    {
        printf("Failed to create renderer: %s\n", SDL_GetError());
        exit(1);
    }

    return r;
}

#endif
