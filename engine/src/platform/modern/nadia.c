// modern/nadia.c
#include <SDL2/SDL.h>

#include <nadia.h>
#include <platform/window.h>

struct core_t
{
    SDL_Event   event; // maybe moving into input.

    int     state;
    char    *title;
};

core_t *nadia_init(config_t *configs)
{
    fprintf(stderr, "Nadia is starting...\n"); fflush(stderr);

    if (!configs)
    {
        fprintf(stderr, "!! Nadia failed: configs pointer is null. !!\n");
        return NULL;
    }

    core_t *core = (core_t *) calloc(1, sizeof(core_t));
    fprintf(stderr, ">> Nadia: Core allocation done.%p\n", (void*)core); fflush(stderr);

    fprintf(stderr, ">> Nadia: Initializing SDL.\n"); fflush(stderr);
    if (SDL_Init(configure_get_libraryflags(configs)) < 0)
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

int nadia_state(const core_t *c)
{ return c->state; }

void nadia_quit(core_t *c)
{
    if (!c) return;
    SDL_Quit();
    free(c);
}

void nadia_poll_events(core_t *c)
{
    SDL_Event e;

    while (SDL_PollEvent(&e))
    {
        if (e.type == SDL_QUIT) c->state = STATE_QUIT;
    }
}

void nadia_await(unsigned int ms)
{ SDL_Delay(ms); }

void nadia_await_seconds(float s)
{ SDL_Delay(s * 1000); }
