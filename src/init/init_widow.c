// init_window.c

#include <SDL2/SDL.h>

#include "defaults.h"
#include "graphics.h"

// Initializes a window with some default values and performs a checking
SDL_Window *create_default_window(void)
{
    SDL_Window *win = SDL_CreateWindow(
        DEFAULT_TITLE,
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, // Position
        DEFAULT_SCREEN_WIDTH,   DEFAULT_SCREEN_HEIGHT,  // Size
        DEFAULT_WINFLAGS
    );

    if (!win)
    {
        printf("Failed to init window: %s\n", SDL_GetError());
        exit(1);
    }
    
    return win;
}

// Initializes a window with custom values and performs a checking
SDL_Window *create_custom_window(const char *title, uint x, uint y, uint w, uint h, int flags)
{
    screen_t area = {w, h, x, y};
    int _flags = flags;

    if (x == 0)
    {
        printf("Warning: Missing initial x position for window. Using default.\n");
        area.x = SDL_WINDOWPOS_CENTERED;
    }
    if (y == 0)
    {
        printf("Warning: Missing initial y position for window. Using default.\n");
        area.y = SDL_WINDOWPOS_CENTERED;
    }
    if (w == 0)
    {
        printf("Warning: Missing initial width for window. Using default.\n");
        area.w = DEFAULT_SCREEN_WIDTH;
    }
    if (h == 0)
    {
        printf("Warning: Missing initial height for window. Using default.\n");
        area.h = DEFAULT_SCREEN_HEIGHT;
    }
    if (flags == 0)
    {
        printf("Warning: Missing initial window flags. Using default.\n");
        _flags = DEFAULT_WINFLAGS;
    }

    SDL_Window *win = SDL_CreateWindow(title, area.x, area.y, area.w, area.h, _flags);
    
    return win;
}
