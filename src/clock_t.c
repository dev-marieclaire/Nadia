#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdint.h>

#include "clock_t.h"

petite_clock_t *create_clock_t(int framerate_target)
{
    petite_clock_t *clock = (petite_clock_t *) malloc(sizeof(petite_clock_t));
    if (!clock) return NULL;
    memset(clock, 0, sizeof(petite_clock_t));
    clock->ms_framerate_target = (double) 1000.0f / (double) framerate_target;

    return clock;
}

double get_delta_time(double start, double end)
{ return (double) ((end - start) / SDL_GetPerformanceFrequency()) * 1000.0f; }

void clock_delay(double delta_time, uint16_t ms_framerate_target)
{
    if (delta_time < ms_framerate_target)
        SDL_Delay((unsigned int) (ms_framerate_target - delta_time));
    // return ms_framerate_target;
}
