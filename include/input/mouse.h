#pragma once
#include <SDL2/SDL.h>

typedef struct mouse_t
{
    int abs_x;
    int abs_y;

    int rel_x;
    int rel_y;

    SDL_Point   click_pos;

    float       sensitivity;
    uint32_t    buttonflags;
    bool        clicking;
    bool        moving;
} mouse_t;
