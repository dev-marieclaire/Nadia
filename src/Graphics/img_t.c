// img.cpp
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Graphics/img_t.h"

img_t *create_img_t(SDL_Renderer *dest, const char *src, const char *name)
{
    img_t *img = (img_t*) malloc(sizeof(img_t));
    if (!img)
    {
        printf("Couldn't allocate memory for '%d'.", name);
        return NULL;
    }

    if (name) img->name = string(name);
    else printf("Warning: No image name set.\n");

    img->texture = load_img_data(src, dest);
    if (!img->texture)
    {
        fprintf(stderr, "Failed to load texture for '%s': %s\n", name, SDL_GetError());
        free(img);
        return NULL;
    }

    SDL_QueryTexture(img->texture, NULL, NULL, &img->w, &img->h);
    printf("'%s' dimensions: %dx%d\n", name, img->w, img->h);

    if (img) return img;
    
    printf("Failed to create '%s' image: %s", name, SDL_GetError());
    return NULL;
}

SDL_Texture *load_img_data(const char *src, SDL_Renderer *dest)
{
    if (!dest)
    {
        printf("Renderer is NULL.\n");
        return NULL;
    }

    SDL_Surface *data = IMG_Load(src); // Turns out this method automatically detects the format.
    if (!data)
    {
        printf("Failed to load %s: %s\n", src, IMG_GetError());
        return NULL;
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(dest, data);

    if (!texture)
    {
        fprintf(stderr, "Couldn't create texture: %s", SDL_GetError());
        return NULL;
    }

    SDL_FreeSurface(data);

    return texture;
}

/* Unused
bool clear_img(SDL_Texture *texture)
{
    if (texture) SDL_DestroyTexture(texture);
    return (!texture) ? true : false;
}

bool reload(img_t *img, const char *src, SDL_Renderer *dest)
{
    if (clear_img(img->texture))
        img->texture = load_img_data(src, dest);
    return (img) ? true : false;
}
*/



void free_img_t(img_t *img)
{
    if (img->texture) SDL_DestroyTexture(img->texture);
    free(img);
}
