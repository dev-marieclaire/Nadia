// nadia.h

#pragma once

#ifndef NADIA_H
#define NADIA_H

#include <stdint.h>

#define NADIA_STATE_INITIALIZING      0x00
#define NADIA_STATE_RUNNING           0x01
#define NADIA_STATE_IDLE              0x02
#define NADIA_STATE_QUIT              0x04
#define NADIA_STATE_INIT_FAILURE      0xFD
#define NADIA_STATE_RUNTIME_FAILURE   0xFF

#define NADIA_SUCCESS_MSG ">> Nadia: success.\n"

#include <platform/config.h>
#include <platform/api.h>
#include <nadia_strings.h>

// Log severity levels, ordered from most to least verbose.
// A message is printed only if its level is >= NADIA_CORE.log_level.
typedef enum
{
    NADIA_LOG_TRACE = 0,
    NADIA_LOG_DEBUG,
    NADIA_LOG_INFO,
    NADIA_LOG_WARN,
    NADIA_LOG_ERROR,
    NADIA_LOG_FATAL
} nadia_log_level_t;

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

    // Shorthand for a plain INFO-level message.
    // Retained for backward compatibility with existing call sites.
    void (*log)(const char *message);

    // Structured logger. Supports printf-style formatting and a severity
    // level that drives both filtering and the output prefix.
    // Prefer the NADIA_LOG_* macros below over calling this directly.
    void (*logf)(nadia_log_level_t level, const char *fmt, ...);

    // Sets the minimum level that will be printed. Anything below this
    // level is discarded silently. Defaults to NADIA_LOG_INFO.
    void (*set_log_level)(nadia_log_level_t level);

    // Enables or disables debug mode. When enabled, the log level drops
    // to NADIA_LOG_TRACE so every message is emitted; when disabled, it
    // returns to NADIA_LOG_INFO.
    void (*set_debug_mode)(uint8_t status);

    /* Input */
    int (*poll_events)(void *event);

    int               state;      // Stores the current execution-time status.
    uint8_t           debug_mode; // Global variable that enables or disables debug mode.
    char             *title;      // Stores the title of the program.
    nadia_log_level_t log_level;  // Current minimum log level.
} nadia_core_t;

extern nadia_core_t NADIA_CORE;

/* LOGGING CONVENIENCE MACROS */

#define NADIA_LOG_TRACE(...)  NADIA_CORE.logf(NADIA_LOG_TRACE, __VA_ARGS__)
#define NADIA_LOG_DEBUG(...)  NADIA_CORE.logf(NADIA_LOG_DEBUG, __VA_ARGS__)
#define NADIA_LOG_INFO(...)   NADIA_CORE.logf(NADIA_LOG_INFO,  __VA_ARGS__)
#define NADIA_LOG_WARN(...)   NADIA_CORE.logf(NADIA_LOG_WARN,  __VA_ARGS__)
#define NADIA_LOG_ERROR(...)  NADIA_CORE.logf(NADIA_LOG_ERROR, __VA_ARGS__)
#define NADIA_LOG_FATAL(...)  NADIA_CORE.logf(NADIA_LOG_FATAL, __VA_ARGS__)

#endif // End of NADIA_H
