#pragma once

#ifndef IMG_H
#define IMG_H

#include <graphics/graphics.h>

/* IMAGE DATATYPE */
typedef struct img_t
{
    int pixels[];
    int w, h; // Image dimensions.
    char *name; // Image name.
} img_t;

/* IMAGE SUBSYSTEM */
typedef struct
{
    img_t   *(*create)(nadia_renderer_t *dest, const char *src, const char *name);
    int     (*blit)(img_t *image, nadia_renderer_t *dest);
    void    (*destroy)(img_t *img);
} nadia_image_t;

extern nadia_image_t NADIA_IMAGE;

#endif // End of IMG_H
