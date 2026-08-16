// modern/nadia.c
#include <SDL2/SDL.h>

#include "nadia.h"
#include "window.h"

struct core_t
{
    SDL_Window      *window;
    SDL_Renderer    *framebuffer;

    SDL_Event   event; // maybe moving into input.

    int     state;
    char    *title;
};

core_t *nadia_init(config_t *configs)
{
    fprintf(stderr, "Nadia is starting...\n"); fflush(stderr);

    core_t *core = (core_t *) calloc(1, sizeof(core_t));
    fprintf(stderr, ">> Nadia: Core allocation done.%p\n", (void*)core); fflush(stderr);

    fprintf(stderr, ">> Nadia: Initializing SDL.\n"); fflush(stderr);
    if (SDL_Init(config_get_libflags(configs)) < 0)
    {
        fprintf(stderr, "! Nadia failed: Couldn't initialize SDL !\n%s", SDL_GetError()); fflush(stderr);
        free(core);
        return NULL;
    }
    fprintf(stderr, ">> Nadia: success.\n"); fflush(stderr);

    core->state = STATE_RUNNING;
    fprintf(stderr, "Nadia is now running.\n\n"); fflush(stderr);

    return core;
}

bool nadia_graphics_init(core_t *c, char *title, config_t *configs)
{
    fprintf(stderr, "Nadia is initializing the graphical environment...\n"); fflush(stderr);

    if (!c)
    {
        fprintf(stderr, "!! Nadia failed: core pointer is null. !!\n");
        return false;
    }

    if (!configs)
    {
        fprintf(stderr, "!! Nadia failed: configs pointer is null. !!\n");
        return false;
    }

    fprintf(stderr, ">> Nadia: Creating screen.\n"); fflush(stderr);
    screen_t screen;
    query_screen(configs, &screen);
    fprintf(stderr, ">> Nadia: success.\n"); fflush(stderr);

    fprintf(stderr, ">> Nadia: Creating window.\n"); fflush(stderr);

    c->window = create_window(
        title, &screen,
        config_get_winflags(configs)
    );

    if (!c->window)
    {
        fprintf(stderr, "!! Nadia failed: Couldn't initialize window. !!\n");
        SDL_Quit();
        free(c);
        return false;
    }

    fprintf(stderr, ">> Nadia: sucess\n"); fflush(stderr);

    fprintf(stderr, ">> Nadia: Creating framebuffer.\n"); fflush(stderr);
    c->framebuffer = SDL_CreateRenderer(c->window, -1, config_get_framebflags(configs));
    if (!c->framebuffer)
    {
        fprintf(stderr, "!! Nadia failed: %s !!\n", SDL_GetError());
        SDL_DestroyWindow(c->window);
        SDL_Quit();
        free(c);
        return false;
    }
    fprintf(stderr, ">> Nadia: success.\n"); fflush(stderr);


    fprintf(stderr, ">> Nadia: Initializing SDL image.\n"); fflush(stderr);
    int img_initted = IMG_Init(config_get_libimageflags(configs));
    if(img_initted & config_get_libimageflags(configs) != config_get_libimageflags(configs))
    {
        printf("IMG_Init: Failed to init required jpg and png support!\n");
        printf("IMG_Init: %s\n", IMG_GetError());
    }
    fprintf(stderr, ">> Nadia: success.\n"); fflush(stderr);

    fprintf(stderr, ">> Nadia: Graphical environment is now ready.\n"); fflush(stderr);

    return true;
}

int nadia_state(const core_t *c)
{ return c->state; }

void nadia_quit(core_t *c)
{
    if (!c) return;
    SDL_DestroyWindow(c->window);
    SDL_DestroyRenderer(c->framebuffer);
    SDL_Quit();
    free(c);
}

void nadia_poll_events(core_t *c)
{
    while (SDL_PollEvent(&c->event))
    {
        if (c->event.type == SDL_QUIT) c->state = STATE_QUIT;
    }
}

void nadia_clear_framebuffer(core_t *c, unsigned int color)
{
    SDL_SetRenderDrawColor(
        c->framebuffer,
        (color>>16)&0xFF,
        (color>>8)&0xFF,
        color&0xFF,
        (color>>24)&0xFF
    );
    SDL_RenderClear(c->framebuffer);
}

void nadia_present(core_t *c)
{ SDL_RenderPresent(c->framebuffer); }

void nadia_await(unsigned int ms)
{ SDL_Delay(ms); }

void nadia_await_seconds(float s)
{ SDL_Delay(s * 1000); }



