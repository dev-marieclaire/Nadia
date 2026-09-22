// platform/old/priv_old.h
#pragma once
#ifndef PRIV_OLD_H
#define PRIV_OLD_H

#include <platform/config.h>
#include <allegro.h>

// Config
struct backend_config_t   { int dummy; };
struct window_config_t    { int gfx_mode; int windowed; };
struct renderer_config_t  { int dummy; };
struct buffer_config_t    { int dummy; };
struct image_config_t     { int color_depth; };

// Graphics
struct nadia_texture_t    { BITMAP *texture; };
struct nadia_renderer_t   { BITMAP *renderer; };
struct nadia_window_t     { int dummy; }; // Allegro doesn't have windows

#endif
