// nadia.h

#pragma once

#ifndef NADIA_H
#define NADIA_H

#define NADIA_STATE_RUNNING   0x01
#define NADIA_STATE_IDLE      0x02
#define NADIA_STATE_QUIT      0x04
#define NADIA_STATE_INIT_FAILURE      0xFD
#define NADIA_STATE_RUNTIME_FAILURE   0xFF

#define DEFAULT_TITLE   "APPLICATION"

#include <config.h>
#include <nadia_strings.h>

// A nadia_core_t object is responsible of storing and handling logical states of the engine.
typedef struct nadia_core_t
{
    int     state;  // Stores the current execution-time status.
    char    *title; // Stores the title of the program.
} nadia_core_t;

// Initializes the logical environment.
nadia_core_t  *nadia_init(config_t *configs);

// Destroys the logical environment.
void nadia_quit(nadia_core_t *c);

// Returns the current state of Nadia.
int nadia_state(const nadia_core_t *c);

// Input
void nadia_poll_events(nadia_core_t *c);

// General
void nadia_await(unsigned int ms);   // Delays execution in miliseconds.
void nadia_await_seconds(unsigned int s);   // Delays execution in seconds.

#endif // End of NADIA_H
