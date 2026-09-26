#pragma once

#ifndef IMAGE_H
#define IMAGE_H

#include <graphics/graphics.h>

typedef struct nadia_image_t nadia_image_t;

/* IMAGE SUBSYSTEM */
typedef struct
{
    // Initializes the image subsystem.
    // Pass NULL to use the library's default configuration.
    // Returns 0 on success, non-zero on failure.
    int  (*init)(const config_t *cfg);

    // Shuts the image subsystem down. Must be called after every image
    // created through this subsystem has been destroyed.
    void (*quit)(void);

    // Creates an image from a file. The texture is loaded through the
    // graphics backend and is owned by the returned image.
    nadia_image_t *(*create)(nadia_renderer_t *dest, const char *src, const char *name);

    // Draws the whole image on the given renderer at (x, y).
    // Returns 0 on success, non-zero on failure.
    int (*blit)(nadia_image_t *image, nadia_renderer_t *dest, int x, int y);

    // Releases the image and its texture.
    void (*destroy)(nadia_image_t *img);

    // Metadata accessors. All of them return 0 or NULL for a NULL image.
    int         (*width)(const nadia_image_t *img);
    int         (*height)(const nadia_image_t *img);
    const char *(*name)(const nadia_image_t *img);
} nadia_image_backend_t;

extern nadia_image_backend_t NADIA_IMAGE;

#endif // End of IMAGE_H
