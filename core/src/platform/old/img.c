// platform/old/img.c

#include <graphics/img.h>

#include <allegro.h>

#include <stdio.h>

image_data_t load_image_data(const char *src, nadia_renderer_t dest)
{
    (void) dest;

    fprintf(stderr, "DEBUG: load_image_data('%s') color_depth=%d\n",
            src ? src : "(null)", get_color_depth());

    BITMAP *data = load_bitmap(src, NULL);
    fprintf(stderr, "DEBUG: load_bitmap returned %p\n", (void *)data);

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
    allegro_message("DEBUG: image=%p texture=%p graphics=%p\n",
       (void *)image,
        image ? (void *)image->texture : NULL,
       (void *)graphics);

    if (!image)        { allegro_message("FAIL: image is NULL\n");        return 0; }
    if (!image->texture){ allegro_message("FAIL: image->texture is NULL\n"); return 0; }
    if (!graphics)     { allegro_message("FAIL: graphics is NULL\n");      return 0; }

    stretch_blit(
        (BITMAP *) image->texture,
        (BITMAP *) graphics->renderer,
        0, 0,
        image->w, image->h,
        0, 0,
        SCREEN_W, SCREEN_H
    );

    return 1;
}

void destroy_image(img_t *img)
{
    if (!img) return;
    if (img->texture) destroy_bitmap((BITMAP *) img->texture);
    free(img);
}
