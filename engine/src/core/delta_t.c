#include <time.h>
#include <stdlib.h>
#include <stdint.h>

#include "core/delta.h"

struct delta_t
{
    unsigned int    start;  // Starting value.
    unsigned int    end;    // Ending value.

    unsigned int    elapsed;    // Stores the difference between the start and end.

    unsigned int    current;    // Current delta value.
    unsigned int    previous;   // Previous delta value.
};

// Stores the elapsed time in miliseconds since the program's execution.
unsigned int delta_store_time(void)
{ return (unsigned int) clock() / CLOCKS_PER_SEC; }

// Delays the application in case the elapsed time is lower than the framerate target in ms.
void dt_delay(uint32_t elapsed_time, uint32_t ms_framerate_target)
{
    if (elapsed_time < ms_framerate_target)
        SDL_Delay(ms_framerate_target - elapsed_time);
}
