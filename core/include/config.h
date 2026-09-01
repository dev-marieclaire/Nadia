#pragma once

#ifndef CONFIG_T_H
#define CONFIG_T_H

#include <display.h>

typedef struct config_t config_t;

config_t *load_default_configs();

void configure_set_libraryflags(config_t *configs, const unsigned int libflags);
void configure_set_image_libraryflags(config_t *configs, const unsigned int libimageflags);
void configure_set_windowflags(config_t *configs, const unsigned int winflags);
void configure_set_framebufferflags(config_t *configs, const unsigned int framebflags);

void configure_set_colordepth(config_t *configs, const unsigned short int color_depth);

void configure_set_display(config_t *configs, const display_t *display);

unsigned int configure_get_libraryflags(const config_t *cfg);
unsigned int configure_get_image_libraryflags(const config_t *cfg);
unsigned int configure_get_windowflags(const config_t *cfg);
unsigned int configure_get_framebufferflags(const config_t *cfg);

unsigned short int configure_get_colordepth(config_t *configs);

unsigned int configure_get_display_w(const config_t *cfg);
unsigned int configure_get_display_h(const config_t *cfg);

unsigned int configure_get_display_x(const config_t *cfg);
unsigned int configure_get_display_y(const config_t *cfg);

char *configure_get_title(const config_t *configs);

#endif // End of CONFIG_T_H
