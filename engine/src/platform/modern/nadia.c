// modern/nadia.c
#include <SDL2/SDL.h>

#include "nadia.h"
// #include "framebuffer.h"
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
    fprintf(stderr, ">>> nadia_init start\n");
    fflush(stderr);

    core_t *core = calloc(1, sizeof(core_t));
    fprintf(stderr, ">>> calloc done: %p\n", (void*)core);
    fflush(stderr);

    if (SDL_Init(config_get_libflags(configs)) < 0)
    {
        fprintf(stderr, "SDL_Init failed: %s\n", SDL_GetError());
        fflush(stderr);
        free(core);
        return NULL;
    }

    fprintf(stderr, ">>> SDL_Init ok\n");
    fflush(stderr);

    return core;
}

bool nadia_graphics_init(core_t *c, char *title, config_t *configs)
{
    if (!c)
    {
        fprintf(stderr, ">> nadia_graphics_init: core is null\n");
        return false;
    }
    if (!configs)
    {
        fprintf(stderr, ">> nadia_graphics_init: configs is null\n");
        return false;
    }
    fprintf(stderr, ">>> Creating screen\n");
    fflush(stderr);

    screen_t screen;
    query_screen(configs, &screen);

    fprintf(stderr, ">>> about to call create_window\n");
    fflush(stderr);

    c->window = create_window(
        title, &screen,
        config_get_winflags(configs)
    );

    if (!c->window)
    {
        fprintf(stderr, "create_window failed\n");
        SDL_Quit();
        free(c);
        return false;
    }
    fprintf(stderr, ">>> window created successfully\n");
    fflush(stderr);

    c->framebuffer = SDL_CreateRenderer(c->window, -1, config_get_framebflags(configs));
    if (!c->framebuffer)
    {
        fprintf(stderr, "SDL_CreateRenderer failed: %s\n", SDL_GetError());
        SDL_DestroyWindow(c->window);
        SDL_Quit();
        free(c);
        return false;
    }
    c->state = STATE_RUNNING;

    return true;
}

void nadia_quit(core_t *c)
{
    if (!c) return;
    SDL_DestroyWindow(c->window);
    SDL_DestroyRenderer(c->framebuffer);
    SDL_Quit();
    free(c);
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

int nadia_state(const core_t *c)
{ return c->state; }

void nadia_poll_events(core_t *c)
{
    while (SDL_PollEvent(&c->event))
    {
        if (c->event.type == SDL_QUIT) c->state = STATE_QUIT;
    }
}
