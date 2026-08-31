#pragma once

#include <display.h>
#include <SDL2/SDL.h>
SDL_Window *create_window(const char *title, display_t *area, unsigned int flags);
