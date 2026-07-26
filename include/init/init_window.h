#include <SDL2/SDL.h>

#include "../game.h"

extern SDL_Window *init_window(void);
extern SDL_Window *init_custom_window(const char *title, uint x, uint y, uint w, uint h, uint flags);
extern SDL_Window *init_window_from_game(game_t *game);
