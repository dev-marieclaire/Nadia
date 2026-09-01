#pragma once

#ifndef PLATROFM_API_H
#define PLATROFM_API_H

#include <nadia.h>
#include <graphics/graphics.h>
#include <display.h>
#include <stdint.h>

typedef struct
{
    // Time
    // Returns the amount of elapsed time in miliseconds since the start of execution.
    uint64_t (*get_ticks_ms)(void);

    void (*sleep_ms)(uint32_t ms);

    // Logging
    void (*log)(const char *message);

    int (*poll_events)(void *event);

    nadia_window_t *(*create_window)(const char *title, display_t *area, unsigned int flags);
    void (*destroy_window)(void *handle);
} platform_api_t;

// Global singleton.
extern platform_api_t NADIA_PLATFORM;

#endif // End of PLATFORM_API_H
