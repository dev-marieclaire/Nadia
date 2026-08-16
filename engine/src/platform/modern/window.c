// window.c
#include <SDL2/SDL.h>

#include "nadia.h"
#include "Graphics/screen_t.h"

#include <stdio.h>
#include <stdlib.h>

// Initializes a window with custom values and performs a checking.
SDL_Window *create_window(const char *title, screen_t *area, unsigned int flags)
{
    fprintf(stderr, ">>> create_window: title=%s x=%u y=%u w=%u h=%u flags=%u\n",
            title ? title : "(null)", area->x, area->y, area->w, area->h, flags);
    fflush(stderr);
    unsigned int _flags = flags;

    if (area->x == 0)
    {
        fprintf(stderr, "Warning: Missing initial x position for window. Using default.\n");
        area->x = SDL_WINDOWPOS_CENTERED;
    }
    if (area->y == 0)
    {
        fprintf(stderr, "Warning: Missing initial y position for window. Using default.\n");
        area->y = SDL_WINDOWPOS_CENTERED;
    }
    if (area->w == 0)
    {
        fprintf(stderr, "Warning: Missing initial width for window. Using default.\n");
        area->w = DEFAULT_SCREEN_WIDTH;
    }
    if (area->h == 0)
    {
        fprintf(stderr, "Warning: Missing initial height for window. Using default.\n");
        area->h = DEFAULT_SCREEN_HEIGHT;
    }
    if (flags == 0)
    {
        fprintf(stderr, "Warning: Missing initial window flags. Using default.\n");
        _flags = DEFAULT_WINFLAGS;
    }

    fprintf(stderr, ">>> calling SDL_CreateWindow...\n");
    fflush(stderr);
    SDL_Window *win = SDL_CreateWindow(title, area->x, area->y, area->w, area->h, _flags);
    fprintf(stderr, ">>> SDL_CreateWindow returned: %p\n", (void*)win);
    fflush(stderr);

    if (!win) {
        fprintf(stderr, ">>> SDL_CreateWindow FAILED: %s\n", SDL_GetError());
        fflush(stderr);
        return NULL;   // ← NUNCA hagas exit() aquí
    }
    
    return win;
}
