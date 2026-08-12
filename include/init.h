#pragma once


#include "Graphics/screen_t.h"
#include "game_t.h"

#ifdef __DJGPP__

#else

#include "init/init_window.h"
#include "init/init_renderer.h"
#include "init/init_img.h"

extern void init_everything(game_t *game, const char *title, screen_t *win_area, int winflags, uint rend_index, int rend_flags);

#endif
