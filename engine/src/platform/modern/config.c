#include <SDL2/SDL.h>

#include <core/config.h>
#include <graphics.h>

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
    configure_set_windowflags(configs, (int) DEFAULT_WINFLAGS);
    configure_set_framebufferflags(configs, DEFAULT_FRAMEB_FLAGS);

    display_t display =
    {
        DEFAULT_DISPLAY_WIDTH,
        DEFAULT_DISPLAY_HEIGHT,
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED
    };

    configure_set_display(configs, &display);

    return configs;
}

// Setter zone
void configure_set_libraryflags(config_t *configs, const unsigned int libflags)
{ configs->libflags = libflags; }

void configure_set_image_libraryflags(config_t *configs, const unsigned int libimageflags)
{ configs->libimageflags = libimageflags; }

void configure_set_windowflags(config_t *configs, const unsigned int winflags)
{ configs->winflags = winflags; }

void configure_set_framebufferflags(config_t *configs, const unsigned int framebflags)
{ configs->framebflags = framebflags; }

void configure_set_display(config_t *configs, const display_t *display)
{ configs->display = *display; }

void configure_set_colordepth(config_t *configs, const int colordepth)
{ configs->color_depth = colordepth; }

// Getter zone
unsigned int configure_get_libraryflags(const config_t *configs)
{ return configs->libflags;}

unsigned int configure_get_image_libraryflags(const config_t *configs)
{ return configs->libimageflags;}

unsigned int configure_get_windowflags(const config_t *configs)
{ return configs->winflags; }

unsigned int configure_get_framebufferflags(const config_t *configs)
{ return configs->framebflags; }

display_t *configure_get_display(config_t *configs)
{ return &configs->display; }

int configure_get_display_w(const config_t *configs)
{ return configs->display.w; }

int configure_get_display_h(const config_t *configs)
{ return configs->display.h; }
