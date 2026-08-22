// old/config_t.h
#include <stdio.h>
#include <stdlib.h>

#include <core/config.h>
#include <graphics.h>

struct config_t
{
    unsigned short int color_depth;
    display_t display;
};

config_t *load_default_configs()
{
    config_t *configs = (config_t *) calloc(1, sizeof(config_t));
    configure_set_colordepth(configs, DEFAULT_COLOR_DEPTH);

    display_t display =
    {
        .w = DEFAULT_DISPLAY_WIDTH,
        .h = DEFAULT_DISPLAY_HEIGHT,
        .x = 0, .y = 0
    };

    configure_set_display(configs, &display);

    return configs;
}

// config_t *set_configs(unsigned short int color_depth, screen_t *screen)
// {
//     config_t *configs = (config_t *) calloc(1, sizeof(config_t));
//     configs->color_depth = color_depth;

//     printf("Queried dimensions: %dx%d", configs->screen.w, configs->screen.h);

//     screen->w = configs->screen.w;
//     screen->h = configs->screen.h;
//     screen->x = configs->screen.x;
//     screen->y = configs->screen.y;

//     return configs;
// }

// Setter zone
// void configure_set_libraryflags(config_t *configs, const unsigned int libflags)
// { configs->libflags = libflags; }

void configure_set_colordepth(config_t *configs, const unsigned short int color_depth)
{ configs->color_depth = color_depth; }

// void configure_set_framebufferflags(config_t *configs, const unsigned int framebflags)
// { configs->framebflags = framebflags; }

void configure_set_display(config_t *configs, const display_t *display)
{ configs->display = *display; }

// Getter zone
// unsigned int configure_get_libflags(const config_t *configs)
// { return configs->libflags;}

unsigned short int configure_get_colordepth(config_t *configs)
{ return configs->color_depth; }

display_t *configure_get_display(config_t *configs)
{ return &configs->display; }

int configure_get_display_w(const config_t *configs)
{ return configs->display.w; }

int configure_get_display_h(const config_t *configs)
{ return configs->display.h; }
