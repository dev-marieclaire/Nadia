// core.h

// This file declares the structure that holds the core elements of an application
// and some default init values. A window pointer, a framebuffer pointer, an event
// handler, a status variable and a title.
// For old systems, it only stores a framebuffer due to the lack of windows.

#pragma once

#ifndef NADIA_H
#define NADIA_H

#define STATE_RUNNING   0x01
#define STATE_IDLE      0x02
#define STATE_QUIT      0x03
#define STATE_INIT_FAILURE      0xFD
#define STATE_RUNTIME_FAILURE   0xFF

#define DEFAULT_TITLE   "APPLICATION"

#include "core/config_t.h"
#include <stdbool.h>

typedef struct core_t core_t;

core_t  *nadia_init(config_t *configs);
bool    nadia_graphics_init(core_t *c, char *title, config_t *configs);
int     nadia_state(const core_t *c);
void    nadia_quit(core_t *c);

// Input
void    nadia_poll_events(core_t *c);

// Graphics
void    nadia_clear_framebuffer(core_t *c, unsigned int color);
void    nadia_present(core_t *c);

// General
void    nadia_await(unsigned int ms);
void    nadia_await_seconds(float s);

#endif // End of CORE_H
