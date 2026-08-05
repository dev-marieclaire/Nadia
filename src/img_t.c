// img.cpp
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "img_t.h"

img_t *create_img_t(SDL_Renderer *dest, const char *src, const char *name)
{
    img_t *img = (img_t*) malloc(sizeof(img_t));
    if (!img) printf("Couldn't allocate memory.");

    img->texture = load_img_data(src, dest);

    if (name)
    {
        img->name = (char*) name;
        size_t len = strlen(img->name);

        img->name = (char*) malloc(len + 1);
        if (img->name == NULL)
        {
            fprintf(stderr, "Malloc failed.\n");
            return NULL;
        }
    }
    else printf("Warning: No image name set.\n");

    if (img->texture)
    {
        img->area.x = img->area.y = 0;

        SDL_QueryTexture(img->texture, NULL, NULL, &img->area.w, &img->area.h);

        printf("Image dimensions: %dx%d\n", img->area.w, img->area.h);

        return img;
    }
    
    printf("Failed to create image: %s", SDL_GetError());
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

void free_img_t(img_t *img)
{
    if (img->texture) SDL_DestroyTexture(img->texture);
    free(img);
}

void change_position(SDL_Rect *rect, int x, int y)
{ rect->x = x; rect->y = y; }
