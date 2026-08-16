#pragma once

#ifdef __MODERN__

#include <SDL2/SDL.h>
extern SDL_Window *create_window(const char *title, screen_t *area, unsigned int flags);

#endif
