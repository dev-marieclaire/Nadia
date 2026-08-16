#include <SDL2/SDL.h>

#include "core/config_t.h"
#include "graphics.h"

struct config_t
{
    unsigned int libflags;
    unsigned int libimageflags;

    unsigned int winflags;
    unsigned int framebflags;

    unsigned short int color_depth;

    screen_t screen;
};

config_t *load_default_configs()
{
    config_t *configs = (config_t *) calloc(1, sizeof(config_t));
    configs->libflags = DEFAULT_SDLFLAGS;
    configs->libimageflags = DEFAULT_IMG_FLAGS;
    configs->winflags = DEFAULT_WINFLAGS;
    configs->framebflags = DEFAULT_FRAMEB_FLAGS;

    configs->screen.w = DEFAULT_SCREEN_WIDTH;
    configs->screen.h = DEFAULT_SCREEN_HEIGHT;
    configs->screen.x = SDL_WINDOWPOS_UNDEFINED;
    configs->screen.y = SDL_WINDOWPOS_UNDEFINED;

    return configs;
}

// config_t *init_configs(unsigned int libflags, unsigned int winflags, unsigned int framebflags, screen_t *screen)
// {
//     config_t *configs = (config_t *) calloc(1, sizeof(config_t));
//     configs->libflags = DEFAULT_SDLFLAGS;
//     configs->libimageflags = DEFAULT_IMG_FLAGS;
//     configs->winflags = winflags;
//     configs->framebflags = framebflags;

//     configs->screen.w = screen->w;
//     configs->screen.h = screen->h;
//     configs->screen.x = screen->x;
//     configs->screen.y = screen->y;

//     return configs;
// }


unsigned int config_get_libflags(const config_t *cfg)
{ return cfg->libflags;}

unsigned int config_get_libimageflags(const config_t *cfg)
{ return cfg->libimageflags;}

unsigned int config_get_winflags(const config_t *cfg)
{ return cfg->winflags; }

unsigned int config_get_framebflags(const config_t *cfg)
{ return cfg->framebflags; }

int config_get_screen_w(const config_t *cfg)
{ return cfg->screen.w; }

int config_get_screen_h(const config_t *cfg)
{ return cfg->screen.h; }
