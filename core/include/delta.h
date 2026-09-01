#pragma once

#ifndef DELTA_H
#define DELTA_H

#include <stdint.h>

// This struct is meant to store many tipes of delta calculations, not only delta time.
typedef struct delta_t
{
    uint64_t    start;  // Starting value.
    uint64_t    end;    // Ending value.

    uint64_t    current;    // Current delta value.

    uint64_t    target; // Target value.
} delta_t;

// Initializes the delta time.
void delta_time_init(delta_t *delta_time, unsigned int target_timelapse);

// Updates the delta time.
void delta_time_update(delta_t *dt);

#endif // End of DELTA_H
