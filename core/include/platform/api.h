#pragma once

#ifndef API_H
#define API_H

#include <nadia.h>
#include <graphics/graphics.h>

#include <stdint.h>

typedef struct
{
    /* Backend */

    /* Module Start-Up and Shut-Down */
    // This is where everything begins, the backend is responsible of managing the
    // protocols, operating system and hardware of the machine and many other things.
    int (*init)(void);  // Initializes the backend.
    int (*init_timer)(void);    // Initializes the timer subsystem.
    int (*init_video)(const char *driver_name); // Initializes the video subsystem.
    int (*init_image)(void); // Initializes the image subsystem.
    // int (*init_audio)(void); // Initializes the audio subsystem.
    // int (*init_music)(void); // Initializes the music subsystem.
    // int (*init_events)(void);    // Initializes the events subsystem.
    void (*quit)(void); // Quits the backend.
} nadia_backend_t;

// Global singleton.
extern nadia_backend_t  NADIA_BACKEND;

#endif // End of API_H
