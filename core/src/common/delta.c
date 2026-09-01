// common/delta.c

#include <delta.h>
#include <platform_api.h>

#include <time.h>
#include <stdlib.h>
#include <stdint.h>

// Initializes the delta time.
void delta_time_init(delta_t *delta_time, unsigned int target_timelapse)
{
    delta_time->target = target_timelapse;
    delta_time->start = NADIA_PLATFORM.get_ticks_ms();
    delta_time->current = target_timelapse;
}

// Updates the delta time.
void delta_time_update(delta_t *dt)
{
    uint64_t now = NADIA_PLATFORM.get_ticks_ms();
    dt->current = now - dt->start;

    // Prevents the spiral of death.
    if (dt->current > 100) dt->current = dt->target;
    dt->start = now;
}
