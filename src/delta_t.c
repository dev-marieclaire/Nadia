#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdint.h>

#include "delta_t.h"

delta_t *create_delta_t(int framerate_target)
{
    delta_t *clock = (delta_t *) malloc(sizeof(delta_t));
    if (!clock) return NULL;

    memset(clock, 0, sizeof(delta_t));

    clock->framerate_target = framerate_target;
    clock->ms_framerate_target = (float) (1000.0f / framerate_target);

    return clock;
}

float get_delta_time(float start, float end)
{ return (float) ((end - start) / SDL_GetPerformanceFrequency()); }

float get_delta_time_in_ms(float calculated_dt)
{ return (float) (calculated_dt * 1000.0f); }

void clock_delay(float delta_time, uint16_t ms_framerate_target)
{
    if (delta_time < ms_framerate_target)
        SDL_Delay((unsigned int) (ms_framerate_target - delta_time));
}
