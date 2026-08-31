#pragma once

#ifndef IMG_H
#define IMG_H

#include <graphics/graphics.h>

typedef void *image_data_t;

typedef struct img_t
{
    image_data_t texture;
    int w, h;
    char *name;
} img_t;

image_data_t load_image_data(const char *src, nadia_renderer_t dest);
img_t *create_image(nadia_renderer_t dest, const char *src, const char *name);
int nadia_blit_image(img_t *image, nadia_graphics_t *graphics);
void destroy_image(img_t *img);

#endif // End of IMG_H
