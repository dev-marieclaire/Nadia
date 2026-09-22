// platform/modern/graphics.c
#include <nadia.h>
#include <platform/api.h>

#include <graphics/graphics.h>

struct nadia_texture_t  { SDL_Texture *texture; };
struct nadia_renderer_t { SDL_Renderer *renderer; };
struct nadia_window_t   { SDL_Window *window; };

nadia_graphics_t *nadia_graphics_init(config_t *configs)
{
    NADIA_CORE.log("Nadia is initializing the graphical environment...\n");

    nadia_graphics_t *g = (nadia_graphics_t *) malloc(sizeof (nadia_graphics_t));

    if (!g)
    {
        NADIA_CORE.log("!! Nadia failed: graphic context pointer is null. !!\n");
        return NULL;
    }

    if (!configs)
    {
        NADIA_CORE.log("!! Nadia failed: configs pointer is null. !!\n");
        return NULL;
    }

    NADIA_CORE.log(">> Nadia: Creating display.\n");
    display_t display = {
        .w = NADIA_CONFIG.get_display_w(),
        .h = NADIA_CONFIG.get_display_h(),
        .x = NADIA_CONFIG.get_display_x(),
        .y = NADIA_CONFIG.get_display_y()
    };

    NADIA_CORE.log(">> Nadia: success.\n");

    NADIA_CORE.log(">> Nadia: Creating window.\n");

    g->window = (nadia_window_t *) NADIA_GFX.create_window(
        NADIA_CONFIG.get_title(), &display,
        NADIA_CONFIG.get_window_flags()
    );

    if (!g->window)
    {
        NADIA_CORE.log("!! Nadia failed: Couldn't initialize window. !!\n");
        SDL_Quit();
        free(g);
        return NULL;
    }

    NADIA_CORE.log(">> Nadia: sucess\n");

    NADIA_CORE.log(">> Nadia: Creating framebuffer.\n");
    g->renderer = (nadia_renderer_t *) SDL_CreateRenderer((SDL_Window *) g->window, -1, NADIA_CONFIG.get_renderer_flags());
    if (!g->renderer)
    {
        NADIA_CORE.log("!! Nadia failed !!\n");
        NADIA_CORE.log(SDL_GetError());
        NADIA_GFX.destroy_window((nadia_window_t *) g->window);
        NADIA_BACKEND.quit();
        NADIA_CORE.quit();
        free(g);
        return NULL;
    }
    NADIA_CORE.log(">> Nadia: success.\n");

    NADIA_CORE.log(">> Nadia: Initializing SDL image.\n");
    int img_initted = IMG_Init((int) NADIA_CONFIG.get_image_flags());

    if((img_initted & (int) NADIA_CONFIG.get_image_flags()) != (int) NADIA_CONFIG.get_image_flags())
    {
        printf("IMG_Init: Failed to init required jpg and png support!\n");
        printf("IMG_Init: %s\n", IMG_GetError());
    }
    NADIA_CORE.log(">> Nadia: success.\n");

    NADIA_CORE.log(">> Nadia: Graphical environment is now ready.\n");

    return g;
}

void nadia_clear_display(nadia_graphics_t *ctx, unsigned int color)
{
    SDL_SetRenderDrawColor(
        (SDL_Renderer *) ctx->renderer,
        (uint8_t) (color>>16)&0xFF,
        (uint8_t) (color>>8)&0xFF,
        (uint8_t) color&0xFF,
        (uint8_t) (color>>24)&0xFF
    );
    SDL_RenderClear((SDL_Renderer *) ctx->renderer);
}

void nadia_graphics_present(nadia_graphics_t *ctx)
{ SDL_RenderPresent((SDL_Renderer *) ctx->renderer); }

void nadia_graphics_quit(nadia_graphics_t *ctx)
{
    SDL_DestroyRenderer((SDL_Renderer *) ctx->renderer);
    SDL_DestroyWindow((SDL_Window *) ctx->window);
    free(ctx);
}
