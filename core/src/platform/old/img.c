// platform/old/img.c

#include <graphics/img.h>

#include <allegro.h>
#include <stdio.h>

static img_t *old_create_image(const char *src, nadia_renderer_t dest)
{
    (void) dest;
    BITMAP *data = load_bitmap(src, NULL);

    if (!data)
    {
        fprintf(stderr, "FAIL: Couldn't load BITMAP '%s'. allegro_error='%s'\n",
                src, allegro_error);
        return NULL;
    }

    return (image_data_t) data;
}

img_t *create_image(nadia_renderer_t dest, const char *src, const char *name)
{
    (void) dest;

    img_t *img = (img_t *) malloc(sizeof(img_t));
    if (!img)
    {
        printf("Couldn't allocate memory for '%s'.", name);
        return NULL;
    }

    image_data_t data = load_image_data(src, dest);
    if (!data)
    {
        printf("Failed to load %s.", src);
        free(img);
        return NULL;
    }

    img->texture = data;

    img->w = ((BITMAP *) data)->w;
    img->h = ((BITMAP *) data)->h;
    img->name = name;

    return img;
}

int nadia_blit_image(img_t *image, nadia_graphics_t *graphics)
{
    blit(
        (BITMAP *) image->texture,
        (BITMAP *) graphics->renderer,
        0, 0,
        0, 0,
        image->w, image->h
    );

    return 1;
}

void destroy_image(img_t *img)
{
    if (!img) return;
    if (img->texture) destroy_bitmap((BITMAP *) img->texture);
    free(img);
}

nadia_image_t NADIA_IMAGE = {
    .create = old_create_image,
    .blit = old_blit,
    .destroy = old_destroy
};
