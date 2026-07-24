// img.cpp
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "img.h"

bool img_t::load(const char *src)
{
    data = IMG_Load(src); // Turns out this method automatically detects the format.
            
    if (!data)
    {
        printf("Failed to load %s: %s\n", src, IMG_GetError());
        return false;
    }

    return true;
}

void img_t::clean()
{
    if (data) SDL_FreeSurface(data);
    if (texture) SDL_DestroyTexture(texture);
}

SDL_Rect img_t::getArea()
{
    SDL_Rect area;
    area.w = data->w;
    area.h = data->h;
    return area;
}
