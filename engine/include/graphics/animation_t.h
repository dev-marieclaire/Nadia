#pragma once

#ifndef ANIMATION_T_H
#define ANIMATION_T_H

#include <stdbool.h>

typedef struct animation_t
{
    unsigned int    duration_ms;
    unsigned int    delay_ms; // Stores the time a frame takes to be replaced in screen.
    unsigned int    timer_ms; // It's used to store the transcurring time.

    unsigned short int  total_frames; // Amount of frame the animation has.
    unsigned short int  frame_index; // The frame that is being displayed.

    char        *name; // Name of the animation. Just in case.
} animation_t;

extern animation_t *create_animation_t(unsigned int delay_ms, unsigned short int total_frames, const char *name);
extern bool update_animation(animation_t *animation, unsigned int delta_ms);

#endif // End of ANIMATION_T_H.
