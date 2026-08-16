// old/nadia.c
#include <allegro.h>
#include <stdio.h>

#include "nadia.h"

struct core_t
{
    BITMAP *framebuffer;

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

bool nadia_graphics_init(core_t *c, char *title, config_t *configs)
{
    if (title) c->title = title;

    fprintf(stderr, "Nadia is initializing the graphical environment...\n"); fflush(stderr);
    set_color_depth(8);

    fprintf(stderr, ">> Nadia: Creating framebuffer.\n"); fflush(stderr);

    if (set_gfx_mode(GFX_AUTODETECT, config_screen_w(configs), config_screen_h(configs), 0, 0) != 0)
    {
        allegro_message("Error: %s\n", allegro_error);
        return false;
    }

    c->framebuffer = screen;

    fprintf(stderr, ">> Nadia: success.\n"); fflush(stderr);

    fprintf(stderr, ">> Nadia: Graphical environment is now ready.\n"); fflush(stderr);

    return true;
}

int nadia_state(const core_t *c)
{ return c->state; }

void nadia_quit(core_t *c)
{
    free(c);
    allegro_exit();
}

void nadia_poll_events(core_t *c)
{ (void) c; }

void nadia_clear_framebuffer(core_t *c, unsigned int color)
{
    clear_to_color(c->framebuffer, makecol(
        (color>>16)&0xFF,
        (color>>8)&0xFF,
        color&0xFF
    ));
}

void nadia_present(core_t *c)
{ (void) c; }

void nadia_await(unsigned int ms)
{ rest(ms); }

void nadia_await_seconds(float s)
{ rest(s * 1000); }
