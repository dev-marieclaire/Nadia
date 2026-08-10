#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

typedef struct img_t
{
    int w, h; // Saves the position and dimensions of the image.
    SDL_Texture *texture; // Image's data.

    char *name; // Name of the image. Just in case.
} img_t;

extern SDL_Texture *load_img_data(const char *src, SDL_Renderer *dest);
extern img_t *create_img_t(SDL_Renderer *dest, const char *src, const char *name);

/* Unused.
extern bool clear_img(SDL_Surface *data, SDL_Texture *texture);
extern bool reload(img_t *img, const char *src);
*/

extern void free_img_t(img_t *img);
