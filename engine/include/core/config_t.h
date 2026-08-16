#pragma once

#ifndef CONFIG_T_H
#define CONFIG_T_H

#include "graphics.h"

typedef struct config_t config_t;

extern config_t *load_default_configs();
extern config_t *init_configs(unsigned int libflags, unsigned int winflags, unsigned int framebflags, screen_t *screen);
extern unsigned int config_get_libflags(const config_t *cfg);
extern unsigned int config_get_libimageflags(const config_t *cfg);
extern unsigned int config_get_winflags(const config_t *cfg);
extern unsigned int config_get_framebflags(const config_t *cfg);
int config_screen_w(const config_t *cfg);
int config_screen_h(const config_t *cfg);
void query_screen(config_t *src, screen_t *out);

#endif // End of CONFIG_T_H
