#pragma once

typedef struct delta_t
{
    unsigned int    start;  // Starting value.
    unsigned int    end;    // Ending value.

    // unsigned int    elapsed;    // Stores the difference between the start and end.

    unsigned int    current;    // Current delta value.
    // unsigned int    previous;   // Previous delta value.
} delta_t;

void delta_time_init(delta_t *delta_time, unsigned int target_timelapse);
unsigned int delta_store_time(void);
