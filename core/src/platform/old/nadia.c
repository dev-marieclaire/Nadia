// old/nadia.c
#include <allegro.h>
#include <stdio.h>

#include <nadia.h>

struct core_t
{
    int     state;
    char    *title;
};

core_t *nadia_init(config_t *configs)
{
    (void) configs;
    setbuf(stderr, NULL);
    setbuf(stdout, NULL);

    fprintf(stderr, "Nadia is starting...\n"); fflush(stderr);
    core_t *core = (core_t *) calloc(1, sizeof(core_t));
    fprintf(stderr, ">> Nadia: Core allocation done.%p\n", (void*)core); fflush(stderr);

    fprintf(stderr, ">> Nadia: Initializing Allegro.\n"); fflush(stderr);
    if (allegro_init() != 0)
    {
        allegro_message("! Nadia failed: Couldn't initialize Allegro !\n%s", allegro_error);
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
    free(c);
    allegro_exit();
}

void nadia_poll_events(core_t *c)
{
    poll_keyboard();

    if (key[KEY_ESC])
    {
        c->state = STATE_QUIT;
    }
}

void nadia_await(unsigned int ms)
{ rest(ms); }

void nadia_await_seconds(float s)
{ rest(s * 1000); }
