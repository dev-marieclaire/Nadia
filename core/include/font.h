#pragma once

#ifndef FONT_H
#define FONT_H

#ifdef __DJGPP__
    struct FONT;
    typedef struct FONT FONT;
#else
    #include <SDL2/SDL.h>
    struct TTF_Font;
    typedef struct TTF_Font TTF_Font;
#endif

typedef struct font_t
{
#ifdef __DJGPP__
    FONT    *data;
#else
    TTF_Font    *data;
    SDL_Color   color;
#endif

    int     size; // In pixels.
    char    *name;
} font_t;

