#pragma once
#ifdef __DJGPP__

// #include <allegro.h>

// typedef struct img_t
// {
//     int w, h; // Saves the position and dimensions of the image.
//     BITMAP *data; // Image's data.

//     char *name; // Name of the image. Just in case.
// } img_t;

// extern img_t *create_img_t(SDL_Renderer *dest, const char *src, const char *name);
// extern DATAFILE *load_img_data(const char *src);
// extern void free_img_t(img_t *img);

#else

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

typedef struct img_t
{
    int w, h; // Saves the position and dimensions of the image.
    SDL_Texture *data; // Image's data.

    char *name; // Name of the image. Just in case.
} img_t;

extern SDL_Texture *load_img_data(const char *src, SDL_Renderer *dest);
extern img_t *create_img_t(SDL_Renderer *dest, const char *src, const char *name);
extern void free_img_t(img_t *img);

#endif
