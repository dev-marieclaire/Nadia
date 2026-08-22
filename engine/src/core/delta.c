// core/delta.c

#include "core/delta.h"

#include <time.h>
#include <stdlib.h>
#include <stdint.h>

void delta_time_init(delta_t *delta_time, unsigned int target_timelapse)
{ delta_time->current = delta_store_time() / target_timelapse; }

// Stores the elapsed time in miliseconds since the program's execution.
unsigned int delta_clock_time(void)
{ return (unsigned int) (clock() * 1000) / CLOCKS_PER_SEC; }
