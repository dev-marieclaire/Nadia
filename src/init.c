// init.c

#include <SDL2/SDL.h>

#include "init.h"
#include "graphics.h"
#include "game_t.h"

#include "defaults.h"

// Inits SDL libs and loads defaults.
void init_everything(game_t *game, const char *title, screen_t *win_area, int winflags, uint rend_index, int rend_flags)
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0)
    {
        printf("Couldn't init SDL: %s\n", SDL_GetError());
        exit(1);
    }

    game->window = create_custom_window(
        title,
        win_area->x, win_area->y,
        win_area->w, win_area->h,
        winflags
    );

    if (!game->window)
    {
        printf("Error: Window doesn't exist.");
        exit(1);
    }

    game->renderer = create_custom_renderer(game->window, rend_index, rend_flags);

    if (!game->renderer)
    {
        printf("Couldn't create SDL Renderer: %s", SDL_GetError());
        exit(1);
    }

    SDL_GetWindowSize(game->window, &game->rect.w, &game->rect.h);
    printf("Window size: %dx%d\n", game->rect.w, game->rect.h);

    init_img(DEFAULT_IMG_FLAGS);
}
