#pragma once

#ifdef __DJGPP__

#else

typedef struct animation_t
{
    uint32_t    duration_ms;
    uint32_t    delay_ms; // Stores the time a frame takes to be replaced in screen.
    uint32_t    timer_ms; // It's used to store the transcurring time.

    uint16_t    total_frames; // Amount of frame the animation has.
    uint16_t    frame_index; // The frame that is being displayed.

    char        *name; // Name of the animation. Just in case.
} animation_t;

extern animation_t *create_animation_t(uint32_t delay_ms, uint16_t total_frames, const char *name);
extern bool update_animation(animation_t *animation, uint32_t delta_ms);

#endif
