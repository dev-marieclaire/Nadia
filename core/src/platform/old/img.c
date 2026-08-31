// platform/old/img.c

#include <graphics/img.h>

#include <allegro.h>

#include <stdio.h>

image_data_t load_image_data(const char *src, nadia_renderer_t dest)
{
    (void) dest;

    // PALETTE pal;

    BITMAP *data = load_bitmap(src, NULL);

    if (!data)
    {
        printf("Couldn't load BITMAP.");
        return NULL;
    }
    // else set_palette(pal);

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
    img->name = NULL;

    return img;
}

int nadia_blit_image(img_t *image, nadia_graphics_t *graphics)
{
    printf("DEBUG: image=%p texture=%p graphics=%p\n",
       (void *)image,
        image ? (void *)image->texture : NULL,
       (void *)graphics);

    if (!image)        { printf("FAIL: image is NULL\n");        return 0; }
    if (!image->texture){ printf("FAIL: image->texture is NULL\n"); return 0; }
    if (!graphics)     { printf("FAIL: graphics is NULL\n");      return 0; }

    blit(
        (BITMAP *) image->texture,
        // (BITMAP *) graphics->renderer,
        screen,
        0, 0, 0, 0,
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
