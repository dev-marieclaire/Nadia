// config.h
#pragma once
#ifndef CONFIG_H
#define CONFIG_H

#define DEFAULT_TITLE   "APPLICATION"

#include <stdint.h>

// ---------------------------
// Opaque Sub-Configurations (Forward Declared)
// The user sees these as pointers, but cannot see inside.
// ---------------------------
typedef struct backend_config_t   backend_config_t;
typedef struct window_config_t    window_config_t;
typedef struct renderer_config_t  renderer_config_t;
typedef struct buffer_config_t    buffer_config_t;
typedef struct image_config_t     image_config_t;

/* DISPLAY CONFIGURATION */
typedef struct display_t {
    int x, y;           // Position on screen (-1 for centered, or specific coords)
    unsigned int w, h;  // Width and Height in pixels
} display_t;

/* GRAPHICAL CONFIGURATION CONTAINER */
typedef struct graphics_config_t
{
    window_config_t    *window;
    renderer_config_t  *renderer;
    buffer_config_t    *buffer;
    image_config_t     *image;
    display_t          *display;
} graphics_config_t;

/* LOGICAL ENVIRONMENT CONFIGURATION CONTAINER */
typedef struct logical_config_t
{
    // Pointers to the opaque sub-configs (managed internally)
    backend_config_t   *backend;
} logical_config_t;

/* GLOBAL CONFIGURATION CONTAINER */
typedef struct config_t {
    logical_config_t  *logic;
    graphics_config_t *graphics;

    // Public fields (user can read/write these directly)
    char *title;
} config_t;

/* CONFIGURATION ACCESS INTERFACE */
typedef struct nadia_config_t {
    // Returns the shared default configuration, creating it on first use.
    // The caller does not own it and must not free it.
    config_t *(*default_config)(void);

    // Reference getters (return the opaque sub-config structs).
    // All of them take the config to read from; NULL returns NULL.
    backend_config_t  *(*get_backend)(const config_t *cfg);
    window_config_t   *(*get_window)(const config_t *cfg);
    renderer_config_t *(*get_renderer)(const config_t *cfg);
    buffer_config_t   *(*get_buffer)(const config_t *cfg);
    image_config_t    *(*get_image)(const config_t *cfg);
    display_t         *(*get_display)(const config_t *cfg);

    // Scalar getters (return the actual values).
    // All of them take the config to read from; NULL returns 0 or NULL.
    int  (*get_display_w)(const config_t *cfg);
    int  (*get_display_h)(const config_t *cfg);
    int  (*get_display_x)(const config_t *cfg);
    int  (*get_display_y)(const config_t *cfg);
    char *(*get_title)(const config_t *cfg);

    int  (*get_backend_flags)(const config_t *cfg);
    int  (*get_window_flags)(const config_t *cfg);
    int  (*get_renderer_flags)(const config_t *cfg);
    int  (*get_image_flags)(const config_t *cfg);

    // Allocates a fresh configuration with default values.
    // The caller owns it and must free it with free_config().
    config_t *(*load_defaults)(void);
} nadia_config_t;

// ---------------------------
// Public API Functions
// ---------------------------

// Loads default configurations (allocates memory).
// Caller must free it with free_config().
config_t *load_default_configs(void);

// Frees all memory associated with a config_t.
// Safe to call with NULL and with partially-constructed configs.
void free_config(config_t *cfg);

// The global configuration interface (defined in config.c)
extern nadia_config_t NADIA_CONFIG;

#endif // CONFIG_H
