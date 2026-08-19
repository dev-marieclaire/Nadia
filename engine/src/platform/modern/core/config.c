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

    display_t display;
};

config_t *load_default_configs()
{
    config_t *configs = (config_t *) calloc(1, sizeof(config_t));
    configure_set_libraryflags(configs, DEFAULT_SDLFLAGS);
    configure_set_image_libraryflags(configs, DEFAULT_IMG_FLAGS);
    configure_set_windowflags(configs, DEFAULT_WINFLAGS);
    configure_set_framebufferflags(framebflags, DEFAULT_FRAMEB_FLAGS)

    display_t display;
    {
        .w = DEFAULT_DISPLAY_WIDTH,
        .h = DEFAULT_DISPLAY_HEIGHT,
        .x = .y = SDL_WINDOWPOS_UNDEFINED
    };

    configure_set_display(configs, &display);

    return configs;
}

// Setter zone
void configure_set_libraryflags(config_t *configs, const unsigned int *libflags)
{ configs->libflags = libflags; }

void configure_set_image_libraryflags(config_t *configs, const unsigned int *libimageflags)
{ configs->libimageflags = libimageflags; }

void configure_set_windowflags(config_t *configs, const unsigned int *winflags)
{ configs->winflags = winflags; }

void configure_set_framebufferflags(config_t *configs, const unsigned int *framebflags)
{ configs->framebflags = framebflags; }

void configure_set_display(config_t *configs, const display_t *display)
{ display = configs->display; }

// Getter zone
unsigned int configure_get_libflags(const config_t *configs)
{ return configs->libflags;}

unsigned int configure_get_libimageflags(const config_t *configs)
{ return configs->libimageflags;}

unsigned int configure_get_winflags(const config_t *configs)
{ return configs->winflags; }

unsigned int configure_get_framebflags(const config_t *configs)
{ return configs->framebflags; }

display_t *configure_get_display(const config_t *configs)
{ return &configs->display; }

int configure_get_display_w(const config_t *configs)
{ return configs->display.w; }

int configure_get_display_h(const config_t *configs)
{ return configs->display.h; }
