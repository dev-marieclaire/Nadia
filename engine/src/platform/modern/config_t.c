#include <SDL2/SDL.h>

#include "nadia.h"
#include "config_t.h"

struct config_t
{
    unsigned int libflags;
    unsigned int winflags;
    unsigned int framebflags;

    unsigned short int color_depth;

    screen_t screen;
};

config_t *load_default_configs()
{
    config_t *configs = calloc(1, sizeof(config_t));
    configs->libflags = DEFAULT_SDLFLAGS;
    configs->winflags = DEFAULT_WINFLAGS;
    configs->framebflags = DEFAULT_FRAMEB_FLAGS;

    configs->screen.w = DEFAULT_SCREEN_WIDTH;
    configs->screen.h = DEFAULT_SCREEN_HEIGHT;
    configs->screen.x = SDL_WINDOWPOS_UNDEFINED;
    configs->screen.y = SDL_WINDOWPOS_UNDEFINED;

    return configs;
}

config_t *init_configs(unsigned int libflags, unsigned int winflags, unsigned int framebflags, screen_t *screen)
{
    config_t *configs = calloc(1, sizeof(config_t));
    configs->libflags = DEFAULT_SDLFLAGS;
    configs->winflags = DEFAULT_WINFLAGS;
    configs->framebflags = DEFAULT_FRAMEB_FLAGS;

    configs->screen.w = screen->w;
    configs->screen.h = screen->h;
    configs->screen.x = screen->x;
    configs->screen.y = screen->y;

    return configs;
}

void query_screen(config_t *src, screen_t *out)
{
    if (!out)
    {
        fprintf(stderr, ">> query_screen: out is null\n");
        return;
    }
    if (src)
    {
        out->w = src->screen.w;
        out->h = src->screen.h;
        out->x = src->screen.x;
        out->y = src->screen.y;
    }
    else
    {
        fprintf(stderr, ">> Nadia couldn't query screen because source is null.");
        fflush(stderr);
    }
}

unsigned int config_get_libflags(const config_t *cfg)
{ return cfg->libflags;}
unsigned int config_get_winflags(const config_t *cfg)
{
    return cfg->winflags;
}
unsigned int config_get_framebflags(const config_t *cfg)
{
    return cfg->framebflags;
}

int config_get_screen_w(const config_t *cfg)
{
    return cfg->screen.w;
}

int config_get_screen_h(const config_t *cfg)
{
    return cfg->screen.h;
}
