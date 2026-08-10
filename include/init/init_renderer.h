#pragma once
#include <SDL2/SDL.h>

extern SDL_Renderer *init_renderer(SDL_Window *w);
extern SDL_Renderer *create_custom_renderer(SDL_Window *w, int index, uint flags);
