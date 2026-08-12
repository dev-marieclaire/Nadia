#pragma once

#ifdef __DJGPP__

#else

#include <SDL2/SDL.h>

extern SDL_Renderer *init_renderer(SDL_Window *w);
extern SDL_Renderer *create_custom_renderer(SDL_Window *w, int index, int flags);

#endif
