#pragma once

#include <stdlib.h>
#include <stdint.h>

typedef struct delta_t
{
    uint16_t    framerate_target; // Stores the amount of frames that will be displayed in a second.
    uint32_t    ms_framerate_target; // framerate_target converted to ms.

    uint32_t    time_ms; // Elapsed time stored in ms.
    uint32_t    previous_time_ms; // Previous time_ms value.
} delta_t;

extern delta_t *create_delta_t(uint16_t framerate_target);
extern void dt_delay(uint32_t elapsed_time, uint32_t ms_framerate_target);
