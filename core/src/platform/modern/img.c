// img.c
#include "graphics/img.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

img_t *create_image(nadia_renderer_t *dest, const char *src, const char *name)
{
    img_t *img = (img_t*) malloc(sizeof(img_t));
    if (!img)
    {
        printf("Couldn't allocate memory for '%s'.", name);
        free(img);
        return NULL;
    }

    if (name) img->name = string(name);
    else printf("Warning: No image name set.\n");

    img->texture = load_image_data(src, dest);
    if (!img->texture)
    {
        fprintf(stderr, "Failed to load texture for '%s': %s\n", name, SDL_GetError());
        free(img);
        return NULL;
    }

    SDL_QueryTexture((SDL_Texture *) img->texture, NULL, NULL, &img->w, &img->h);
    printf("'%s' dimensions: %dx%d\n", name, img->w, img->h);

    return img;
}

image_data_t *load_image_data(const char *src, nadia_renderer_t *dest)
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

    SDL_Texture *texture = SDL_CreateTextureFromSurface((SDL_Renderer *) dest, data);

    if (!texture)
    {
        fprintf(stderr, "Couldn't create texture: %s", SDL_GetError());
        return NULL;
    }

    SDL_FreeSurface(data);

    return (image_data_t *) texture;
}

int nadia_blit_image(img_t *image, nadia_graphics_t *graphics)
{
    SDL_Rect rect = {
        0, 0, image->w, image->h
    };

    int result = SDL_RenderCopy(
        (SDL_Renderer *) graphics->renderer,
        (SDL_Texture *) image->texture, NULL, &rect
    );

    return result;
}

void free_image(img_t *img)
{
    if (img->texture) SDL_DestroyTexture((SDL_Texture *) img->texture);
    free(img);
}
