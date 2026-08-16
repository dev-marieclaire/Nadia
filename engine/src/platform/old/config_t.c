// old/config_t.h
#include <stdio.h>
#include <stdlib.h>

#include "config_t.h"
#include "nadia.h"

struct config_t
{
    unsigned short int color_depth;
    screen_t screen;
};

config_t *load_default_configs()
{
    config_t *configs = (config_t *) calloc(1, sizeof(config_t));
    configs->color_depth = DEFAULT_COLOR_DEPTH;

    configs->screen.w = DEFAULT_SCREEN_WIDTH;
    configs->screen.h = DEFAULT_SCREEN_HEIGHT;
    configs->screen.x = configs->screen.x = 0;

    return configs;
}

config_t *set_configs(unsigned short int color_depth, screen_t *screen)
{
    config_t *configs = (config_t *) calloc(1, sizeof(config_t));
    configs->color_depth = color_depth;

    printf("Queried dimensions: %dx%d", configs->screen.w, configs->screen.h);

    screen->w = configs->screen.w;
    screen->h = configs->screen.h;
    screen->x = configs->screen.x;
    screen->y = configs->screen.y;

    return configs;
}

void query_screen(config_t *src, screen_t *out)
{
    if (src) out = &src->screen;
    else
    {
        fprintf(stderr, ">> Nadia couldn't query screen because source is null.");
        fflush(stderr);
    }
}
