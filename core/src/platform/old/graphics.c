// platform/old/graphics.c

#include <allegro.h>

#include <nadia.h>
#include <graphics/graphics.h>

#include <stdlib.h>
#include <stdio.h>

struct nadia_texture_t  { BITMAP *texture; };
struct nadia_renderer_t { BITMAP *renderer; };
struct nadia_window_t   { short short int dummy; };

nadia_graphics_t *nadia_graphics_init(config_t *configs)
{
    NADIA_PLATFORM.log("Nadia is initializing the graphical environment...\n");
    
    if (!configs)
    {
        NADIA_PLATFORM.log("!! Nadia failed: configs pointer is null. !!\n");
        return NULL;
    }

    nadia_graphics_t *g = (nadia_graphics_t *) malloc(sizeof (nadia_graphics_t));

    if (!g)
    {
        NADIA_PLATFORM.log("!! Nadia failed: graphic context pointer is null. !!\n");
        return NULL;
    }

    set_color_depth(configure_get_colordepth(configs));

    NADIA_PLATFORM.log(">> Nadia: Creating framebuffer.\n");

    memset(g, 0, sizeof(nadia_graphics_t));

    if (set_gfx_mode(GFX_AUTODETECT, configure_get_display_w(configs), configure_get_display_h(configs), 0, 0) != 0)
    {
        NADIA_PLATFORM.log("Error: %s\n", allegro_error);
        free(g);
        return NULL;
    }

    BITMAP *backbuffer = create_bitmap(configure_get_display_w(configs), configure_get_display_h(configs));
    if (!backbuffer) {
        allegro_message("Error: cannot create backbuffer\n");
        free(g);
        return NULL;
    }

    g->renderer = (nadia_renderer_t) screen;
    g->framebuffer.data = (nadia_texture_t) backbuffer;
    g->framebuffer.width = configure_get_display_w(configs);
    g->framebuffer.height = configure_get_display_h(configs);

    NADIA_PLATFORM.log(">> Nadia: success.\n");
    NADIA_PLATFORM.log(">> Nadia: Graphical environment is now ready.\n");

    return g;
}

void nadia_clear_display(nadia_graphics_t *ctx, unsigned int color)
{
    if (!ctx || !ctx->framebuffer.data) return;
    clear_to_color((BITMAP *)ctx->framebuffer.data, makecol(
        (color >> 16) & 0xFF,
        (color >> 8) & 0xFF,
        color & 0xFF
    ));
}

void nadia_graphics_present(nadia_graphics_t *ctx)
{
    if (!ctx || !ctx->framebuffer.data) return;
    vsync();
    blit(ctx->framebuffer.data, ctx->renderer, 0, 0, 0, 0, ctx->framebuffer.width, ctx->framebuffer.height);
}

void nadia_graphics_quit(nadia_graphics_t *ctx)
{
    if (!ctx) return;
    set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
    free(ctx);
}
