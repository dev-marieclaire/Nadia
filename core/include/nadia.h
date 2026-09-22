// nadia.h

#pragma once

#ifndef NADIA_H
#define NADIA_H

#define NADIA_STATE_INITIALIZING 0x00
#define NADIA_STATE_RUNNING   0x01
#define NADIA_STATE_IDLE      0x02
#define NADIA_STATE_QUIT      0x04
#define NADIA_STATE_INIT_FAILURE      0xFD
#define NADIA_STATE_RUNTIME_FAILURE   0xFF

#include <platform/config.h>
#include <platform/api.h>
#include <nadia_strings.h>

typedef struct
{
    void (*init)(config_t *configs); // Initializes the core.
    void (*quit)(void);
    int (*get_state)(void);

    /* Hi-Res Timer. */
    // Returns the amount of elapsed time in miliseconds since the start of execution.
    uint64_t (*get_ticks_ms)(void);
    void (*sleep_ms)(uint32_t ms); // Pauses execution.

    /* Debug Printing and Logging. */
    void (*log)(const char *message);   // Registers a log message.
    void (*set_debug_mode)(uint8_t status);    // Enables the debug mode.

    /* Input */
    int (*poll_events)(void *event);

    int     state;  // Stores the current execution-time status.
    uint8_t debug_mode; // Global variable that enables or disables debug mode.
    char    *title; // Stores the title of the program.
} nadia_core_t;

extern nadia_core_t NADIA_CORE;

#endif // End of NADIA_H
