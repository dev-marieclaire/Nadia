// img.c
#include <graphics/img.h>
#include <platform/api.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

static img_t *modern_create_image(nadia_renderer_t *dest, const char *src, const char *name)
{
    img_t *img = (img_t*) malloc(sizeof(img_t));
    

    if (!img)
    {
        NADIA_CORE.log("Nadia Error: Couldn't allocate memory for image.");
        // NADIA_LIB.log("Couldn't allocate memory for '%s'.", name);
        free(img);
        return NULL;
    }

    if (name) img->name = strdup(name);
    else printf("Warning: No image name set.\n");

    img->texture = NADIA_GFX.load_texture(src, dest);
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

static int modern_blit(img_t *image, nadia_renderer_t *dest)
{
    SDL_Rect rect = {
        0, 0, image->w, image->h
    };

    return SDL_RenderCopy(
        (SDL_Renderer *) dest,
        (SDL_Texture *) image->texture, NULL, &rect
    );
}

static void modern_destroy(img_t *img)
{
    if (img)
    {
        if (img->texture) SDL_DestroyTexture((SDL_Texture *) img->texture);
        free(img);
    }
}

nadia_image_t NADIA_IMAGE = {
    .create = modern_create_image,
    .blit = modern_blit,
    .destroy = modern_destroy
};
