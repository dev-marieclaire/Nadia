#pragma once

#include <stdlib.h>
#include <stdint.h>

typedef struct petite_clock_t
{
    double      delta_time;
    double      ms_framerate_target;

    uint64_t    beginning;
    uint64_t    ending;

    uint16_t    counter;
} petite_clock_t;

extern petite_clock_t *create_clock_t(int framerate_target);
extern double get_delta_time(double start, double end);
extern void clock_delay(double delta_time, uint16_t ms_framerate_target);
