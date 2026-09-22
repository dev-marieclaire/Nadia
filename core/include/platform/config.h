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
    logical_config_t *logic;
    graphics_config_t *graphics;
    
    // Public fields (user can read/write these directly)
    char *title;
} config_t;

/* CONFIGURATION ACCESS INTERFACE */
typedef struct nadia_config_t {
    // A full copy of the configuration (or just a reference).
    // We keep it as a pointer here to avoid huge stack copies.
    config_t *configuration;

    // Reference getters (return the opaque sub-config structs)
    backend_config_t  *(*get_backend)(void);
    window_config_t   *(*get_window)(void);
    renderer_config_t *(*get_renderer)(void);
    buffer_config_t   *(*get_buffer)(void);
    image_config_t    *(*get_image)(void);
    display_t         *(*get_display)(void);

    int (*get_display_w)(void);
    int (*get_display_h)(void);

    int (*get_display_x)(void);
    int (*get_display_y)(void);

    // Flag/value getters (return the actual scalar values)
    uint32_t (*get_backend_flags)(void);
    uint32_t (*get_window_flags)(void);
    uint32_t (*get_renderer_flags)(void);
    // size_t   (*get_buffer_flags)(void); // returns buffer size
    int      (*get_image_flags)(void);

    config_t *(*load_defaults)(void);
    char *(*get_title)(void);
} nadia_config_t;

// ---------------------------
// Public API Functions
// ---------------------------

// Loads default configurations (allocates memory).
// Caller must free it with free_config().
config_t *load_default_configs(void);

// Frees all memory associated with a config_t.
void free_config(config_t *cfg);

// The global configuration interface (defined in config.c)
extern nadia_config_t NADIA_CONFIG;

#endif // CONFIG_H
