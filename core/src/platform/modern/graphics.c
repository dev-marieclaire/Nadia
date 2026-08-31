// platform/modern/graphics.c

#include <nadia.h>
#include <graphics/graphics.h>
#include <platform/window.h>

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
    display_t display;

    display.w = configure_get_display_w(configs);
    display.h = configure_get_display_h(configs);

    fprintf(stderr, ">> Nadia: success.\n"); fflush(stderr);

    fprintf(stderr, ">> Nadia: Creating window.\n"); fflush(stderr);

    g->window = (nadia_window_t) create_window(
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
    g->renderer = (nadia_renderer_t) SDL_CreateRenderer((SDL_Window *) g->window, -1, configure_get_framebufferflags(configs));
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
    int img_initted = IMG_Init(configure_get_image_libraryflags(configs));
    if(img_initted & configure_get_image_libraryflags(configs) != configure_get_image_libraryflags(configs))
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
        (color>>16)&0xFF,
        (color>>8)&0xFF,
        color&0xFF,
        (color>>24)&0xFF
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
