#pragma once

#include <stdlib.h>
#include <stdint.h>

typedef struct delta_t
{
    float       delta_time;
    float       framerate_target;

    float       ms_delta_time;
    float       ms_framerate_target;

    uint64_t    beginning;
    uint64_t    ending;
} delta_t;

extern delta_t *create_delta_t(int framerate_target);
extern float get_delta_time(float start, float end);
extern float get_delta_time_in_ms(float calculated_dt);
extern void clock_delay(float delta_time, uint16_t ms_framerate_target);
