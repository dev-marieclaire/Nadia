#pragma once

typedef struct animation_t
{
    float       duration;
    float       delay;
    float       timer;
    float       progress;

    uint16_t    total_frames;
    uint16_t    frame_index;

    char        *name;
} animation_t;

extern animation_t *create_animation_t(float delay, uint16_t total_frames, const char *name);
