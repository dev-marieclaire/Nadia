// modern/nadia.c
#include <nadia.h>

#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdio.h>

// Initializes the logical environment.
nadia_core_t *nadia_init(config_t *configs)
{
    fprintf(stderr, "Nadia is starting...\n"); fflush(stderr);

    fprintf(stderr, ">> Nadia: Loading configurations.");
    if (!configs) // Checks if the configuration pointer is valid.
    {
        fprintf(stderr, "!! Nadia failed: configs pointer is null. !!\n"); fflush(stderr);
        return NULL;
    }

    // Allocates nadia_core_t.
    nadia_core_t *core = (nadia_core_t *) malloc(sizeof(nadia_core_t));
    fprintf(stderr, ">> Nadia: Core allocation done.%p\n", (void*)core); fflush(stderr);

    // Initializes the library.
    fprintf(stderr, ">> Nadia: Initializing SDL.\n"); fflush(stderr);
    if (SDL_Init(configure_get_libraryflags(configs)) < 0)
    {   // Displays a message and prevents memory leak.
        fprintf(stderr, "! Nadia failed: Couldn't initialize SDL !\n%s", SDL_GetError()); fflush(stderr);
        free(core);
        return NULL;
    }
    fprintf(stderr, ">> Nadia: success.\n"); fflush(stderr);

    // If everything went fine, then the status is set to RUNNING.
    core->state = NADIA_STATE_RUNNING;
    fprintf(stderr, "Nadia is now running.\n\n"); fflush(stderr);

    return core;
}

// Destroys the logical environment.
void nadia_quit(nadia_core_t *c)
{
    SDL_Quit();

    if (!c) return;
    free(c->title);
    free(c);
}

// Returns the current state of Nadia.
int nadia_state(const nadia_core_t *c)
{ return c->state; }

void nadia_poll_events(nadia_core_t *c)
{
    SDL_Event e;

    while (SDL_PollEvent(&e))
    {
        if (e.type == SDL_QUIT) c->state = NADIA_STATE_QUIT;
    }
}

// Delays execution in miliseconds.
void nadia_await(unsigned int ms)
{ SDL_Delay(ms); }

// Delays execution in seconds.
void nadia_await_seconds(unsigned int s)
{ SDL_Delay(s * 1000); }
