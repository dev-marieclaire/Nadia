// platform/modern/graphics.c
#include <nadia.h>
#include <platform_api.h>

#include <graphics/graphics.h>

struct nadia_texture_t  { SDL_Texture *texture; };
struct nadia_renderer_t { SDL_Renderer *renderer; };
struct nadia_window_t   { SDL_Window *window; };

nadia_graphics_t *nadia_graphics_init(config_t *configs)
{
    fprintf(stderr, "Nadia is initializing the graphical environment...\n"); fflush(stderr);

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

    fprintf(stderr, ">> Nadia: Creating display.\n"); fflush(stderr);
    display_t display = {
        .w = configure_get_display_w(configs),
        .h = configure_get_display_h(configs),
        .x = configure_get_display_x(configs),
        .y = configure_get_display_y(configs)
    };

    fprintf(stderr, ">> Nadia: success.\n"); fflush(stderr);

    fprintf(stderr, ">> Nadia: Creating window.\n"); fflush(stderr);

    g->window = (nadia_window_t *) NADIA_PLATFORM.create_window(
        configure_get_title(configs), &display,
        configure_get_windowflags(configs)
    );

    if (!g->window)
    {
        fprintf(stderr, "!! Nadia failed: Couldn't initialize window. !!\n");
        SDL_Quit();
        free(g);
        return NULL;
    }

    fprintf(stderr, ">> Nadia: sucess\n"); fflush(stderr);

    fprintf(stderr, ">> Nadia: Creating framebuffer.\n"); fflush(stderr);
    g->renderer = (nadia_renderer_t *) SDL_CreateRenderer((SDL_Window *) g->window, -1, configure_get_framebufferflags(configs));
    if (!g->renderer)
    {
        fprintf(stderr, "!! Nadia failed: %s !!\n", SDL_GetError());
        SDL_DestroyWindow((SDL_Window *) g->window);
        SDL_Quit();
        free(g);
        return NULL;
    }
    fprintf(stderr, ">> Nadia: success.\n"); fflush(stderr);

    fprintf(stderr, ">> Nadia: Initializing SDL image.\n"); fflush(stderr);
    int img_initted = IMG_Init((int) configure_get_image_libraryflags(configs));
    if((img_initted & (int) configure_get_image_libraryflags(configs)) != (int) configure_get_image_libraryflags(configs))
    {
        printf("IMG_Init: Failed to init required jpg and png support!\n");
        printf("IMG_Init: %s\n", IMG_GetError());
    }
    fprintf(stderr, ">> Nadia: success.\n"); fflush(stderr);

    fprintf(stderr, ">> Nadia: Graphical environment is now ready.\n"); fflush(stderr);

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
