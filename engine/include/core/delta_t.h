#pragma once

#include <stdlib.h>
#include <stdint.h>

typedef struct delta_t;

delta_t *create_delta_t(void);
void dt_delay(uint32_t elapsed_time, uint32_t ms_framerate_target);
