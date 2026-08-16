// modern/graphics_t.c
#include <SDL2/SDL.h>

#include "graphics.h"
#include "nadia.h"

struct graphics_t
{
    SDL_Renderer   *renderer;
    SDL_Window      *window;
};
