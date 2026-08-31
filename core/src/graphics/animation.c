// graphics/animations_t.c
#include <graphics/animation.h>

#include "strings.h"
#include <stdlib.h>
#include <stdio.h>

animation_t *create_animation_t(unsigned int delay_ms, unsigned short int total_frames, const char *name)
{
    animation_t *animation = (animation_t *) malloc(sizeof(animation_t));
    if (!animation)
    {
        fprintf(stderr, "Couldn't create '%s' animation.", name);
        return NULL;
    }

    animation->delay_ms = delay_ms;

    animation->timer_ms = 0;
    animation->total_frames = total_frames;
    animation->duration_ms = animation->delay_ms * animation->total_frames;
    animation->frame_index = 0;
    animation->name = string(name);

    return animation;
}

// Returns true when the animation reaches the end.
bool update_animation(animation_t *animation, unsigned int delta_ms)
{
    if (animation->total_frames <= 1) return true;

    animation->timer_ms += delta_ms;
    if (animation->timer_ms >= animation->duration_ms)
    {
        animation->timer_ms = animation->frame_index = 0;
        return true;
    }

    animation->frame_index = animation->timer_ms / animation->delay_ms;
    return false;
}
