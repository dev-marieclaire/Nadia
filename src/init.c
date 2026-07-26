// init.c

#include <SDL2/SDL.h>

#include "init/init_window.h"
#include "init/init_windefaults.h"
#include "init/init_renderer.h"
#include "init/init_img.h"

#include "game.h"

// Inits SDL libs and loads defaults.
void init_everything(game_t *game)
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0)
    {
        printf("Couldn't init SDL: %s\n", SDL_GetError());
        exit(1);
    }

    game->window = init_window_from_game(game);

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_SetHint(SDL_HINT_VIDEODRIVER, "x11");

    const char *driver = SDL_GetCurrentVideoDriver();
    printf("Current video driver: %s\n", driver ? driver : "none");

    if (game->window != NULL)
    {
        game->renderer = init_renderer(game->window);

        if (!game->renderer)
        {   printf("Couldn't create SDL Renderer: %s", SDL_GetError());
            exit(1);
        }
    }
    else
    { printf("Error: Window doesn't exist."); exit(1); }

    SDL_GetWindowSize(game->window, &game->rect.w, &game->rect.h);
    printf("Window size: %dx%d\n", game->rect.w, game->rect.h);

    game->center = { game->rect.w >> 1, game->rect.h >> 1 };

    init_img(DEFAULT_IMG_FLAGS);
}
