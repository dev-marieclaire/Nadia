#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdint.h>

#include "delta_t.h"

// Initializes delta_t variables.
delta_t *create_delta_t(uint16_t framerate_target)
{
    delta_t *delta = (delta_t *) malloc(sizeof(delta_t));
    if (!delta) return NULL;

    memset(delta, 0, sizeof(delta_t));

    delta->framerate_target = framerate_target;
    delta->ms_framerate_target = 1000 / framerate_target;
    delta->previous_time_ms = SDL_GetTicks();

    return delta;
}

// Delays the application in case the elapsed time is lower than the framerate target in ms.
void dt_delay(uint32_t elapsed_time, uint32_t ms_framerate_target)
{
    if (elapsed_time < ms_framerate_target)
        SDL_Delay(ms_framerate_target - elapsed_time);
}
