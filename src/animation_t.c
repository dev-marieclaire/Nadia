#include <SDL2/SDL.h>

#include "animation_t.h"

#include "strings.h"

animation_t *create_animation_t(float delay, uint16_t total_frames, const char *name)
{
    animation_t *animation = (animation_t *) malloc(sizeof(animation_t));
    animation->duration = delay * total_frames;
    animation->delay = delay;
    animation->timer = animation->progress = 0.0f;
    animation->total_frames = total_frames;
    animation->frame_index = 0;
    animation->name = string(name);

    if (!animation)
    {
        fprintf(stderr, "Couldn't create animation.");
        return NULL;
    }

    return animation;
}

