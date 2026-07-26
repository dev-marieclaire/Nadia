// init_window.c

#include <SDL2/SDL.h>

#include "init/init_windefaults.h"
#include "game.h"

// Initializes a window with some default values and performs a checking
SDL_Window *init_window(void)
{   SDL_Window *win = SDL_CreateWindow( TITLE,
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, // Position
        DEFAULT_SCREEN_WIDTH,   DEFAULT_SCREEN_HEIGHT,  // Size
        DEFAULT_WINFLAGS
    );

    if (!win)
    {   printf("Failed to init window: %s\n", SDL_GetError());
        exit(1);
    }
    
    return win;
}

// Initializes a window with custom values and performs a checking
SDL_Window *init_custom_window(const char *title, uint x, uint y, uint w, uint h, uint flags)
{   SDL_Window *win = SDL_CreateWindow(title, x, y, w, h, flags);

    if (!win)
    {   printf("Failed to init window: %s\n", SDL_GetError());
        exit(1);
    }
    
    return win;
}

SDL_Window *init_window_from_game(game_t *game)
{
    if (game->win_x == 0)
    {
        printf("Warning: Missing initial x position for window. Using default.\n");
        game->win_x = SDL_WINDOWPOS_CENTERED;
    }
    if (game->win_y == 0)
    {
        printf("Warning: Missing initial y position for window. Using default.\n");
        game->win_y = SDL_WINDOWPOS_CENTERED;
    }
    if (game->win_w == 0)
    {
        printf("Warning: Missing initial width for window. Using default.\n");
        game->win_w = DEFAULT_SCREEN_WIDTH;
    }
    if (game->win_h == 0)
    {
        printf("Warning: Missing initial height for window. Using default.\n");
        game->win_h = DEFAULT_SCREEN_HEIGHT;
    }
    if (game->winflags == 0)
    {
        printf("Warning: Missing initial window flags. Using default.\n");
        game->winflags = DEFAULT_WINFLAGS;
    }

    SDL_Window *win = SDL_CreateWindow(
        game->title,
        game->win_x, game->win_y,
        game->win_w, game->win_h,
        game->winflags);

    if (!win)
    {   printf("Failed to init window: %s\n", SDL_GetError());
        exit(1);
    }
    
    return win;
}
