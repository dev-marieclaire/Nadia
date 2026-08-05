#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

typedef struct img_t
{
    SDL_Rect area;
    SDL_Texture *texture;

    char *name;
} img_t;

extern SDL_Texture *load_img_data(const char *src, SDL_Renderer *dest);
extern img_t *create_img_t(SDL_Renderer *dest, const char *src, const char *name);


extern bool clear_img(SDL_Surface *data, SDL_Texture *texture);
extern bool reload(img_t *img, const char *src);
extern void free_img_t(img_t *img);

extern void change_position(img_t *img, int x, int y);
