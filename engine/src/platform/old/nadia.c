// old/nadia.c
#include <allegro.h>
#include <stdio.h>

#include "nadia.h"
#include "config_t.h"

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

    fprintf(stderr, ">>> Nadia init <<\n");
    fflush(stderr);
    core_t *core = (core_t *) calloc(1, sizeof(core_t));

    if (allegro_init() != 0) return NULL;
    return core;
}

bool nadia_graphics_init(core_t *c, char *title, config_t *configs)
{
    if (title) c->title = title;

    fprintf(stderr, ">>> Graphics init <<\n");
    fflush(stderr);
    set_color_depth(8);

    screen_t area;
    // query_screen(configs, &screen);
    area.w = DEFAULT_SCREEN_WIDTH;
    area.h = DEFAULT_SCREEN_HEIGHT;

    printf("Resolution: %dx%d", area.w, area.h);

    if (set_gfx_mode(GFX_AUTODETECT, area.w, area.h, 0, 0) != 0)
    {
        allegro_message("Error: %s\n", allegro_error);
        return false;
    }

    c->framebuffer = screen;

    c->state = STATE_RUNNING;

    return true;
}

void nadia_quit(core_t *c)
{
    free(c);
    allegro_exit();
}

int nadia_state(const core_t *c)
{ return c->state; }

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
