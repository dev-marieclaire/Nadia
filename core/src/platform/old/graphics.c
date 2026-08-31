// platform/old/graphics.c

#include <allegro.h>

#include <nadia.h>
#include <graphics/graphics.h>

#include <stdlib.h>
#include <stdio.h>

nadia_graphics_t *nadia_graphics_init(config_t *configs)
{
    printf(stderr, "Nadia is initializing the graphical environment...\n"); fflush(stderr);

    nadia_graphics_t *g = (nadia_graphics_t *) malloc(sizeof (nadia_graphics_t));

    if (!g)
    {
        fprintf(stderr, "!! Nadia failed: graphic context pointer is null. !!\n");
        return NULL;
    }

    if (!configs)
    {
        fprintf(stderr, "!! Nadia failed: configs pointer is null. !!\n");
        return NULL;
    }

    set_color_depth(configure_get_colordepth(configs));

    fprintf(stderr, ">> Nadia: Creating framebuffer.\n"); fflush(stderr);

    g->renderer = NULL;

    if (set_gfx_mode(GFX_AUTODETECT, configure_get_display_w(configs), configure_get_display_h(configs), 0, 0) != 0)
    {
        allegro_message("Error: %s\n", allegro_error);
        return false;
    }

    g->framebuffer.data = (nadia_texture_t) screen;

    fprintf(stderr, ">> Nadia: success.\n"); fflush(stderr);

    fprintf(stderr, ">> Nadia: Graphical environment is now ready.\n"); fflush(stderr);

    return g;
}

void nadia_clear_display(nadia_graphics_t *ctx, unsigned int color)
{
    clear_to_color(ctx->framebuffer.data, makecol(
        (color>>16)&0xFF,
        (color>>8)&0xFF,
        color&0xFF
    ));
}

void nadia_graphics_present(nadia_graphics_t *ctx)
{ screen = ctx->framebuffer.data; }

void nadia_graphics_quit(nadia_graphics_t *ctx)
{
    // set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
    // readkey();
    free(ctx);
}
