// old/nadia.c
#include <nadia.h>

#include <allegro.h>
#include <stdlib.h>
#include <stdio.h>

// Initializes the logical environment.
nadia_core_t *nadia_init(config_t *configs)
{
    // nadia_config_t was unused for setting up a logical environment in Allegro.
    (void) configs;
    setbuf(stderr, NULL);
    setbuf(stdout, NULL);

    fprintf(stderr, "Nadia is starting...\n"); fflush(stderr);

    // Allocates nadia_core_t.
    nadia_core_t *core = (nadia_core_t *) malloc(sizeof(nadia_core_t));
    fprintf(stderr, ">> Nadia: Core allocation done.%p\n", (void*)core); fflush(stderr);

    // Initializes the library.
    fprintf(stderr, ">> Nadia: Initializing Allegro.\n"); fflush(stderr);
    if (allegro_init() != 0)
    {   // Displays a message and prevents memory leak.
        allegro_message("! Nadia failed: Couldn't initialize Allegro !\n%s", allegro_error);
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
    allegro_exit();
    
    if (!c) return;
    free(c->title);
    free(c);
}

// Returns the current state of Nadia.
int nadia_state(const nadia_core_t *c)
{ return c->state; }

void nadia_poll_events(nadia_core_t *c)
{
    poll_keyboard();

    if (key[KEY_ESC])
    {
        c->state = NADIA_STATE_QUIT;
    }
}

// Delays execution in miliseconds.
void nadia_await(unsigned int ms)
{ rest(ms); }

// Delays execution in seconds.
void nadia_await_seconds(float s)
{ rest(s * 1000); }
