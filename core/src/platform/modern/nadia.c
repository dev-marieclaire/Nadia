// modern/nadia.c
#include <nadia.h>
#include <platform/api.h>

#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdio.h>

/* NADIA CORE */

// Initializes the logical environment.
void init(config_t *configs)
{
    NADIA_CORE.log("Nadia is starting...\n");

    NADIA_CORE.log(">> Nadia: Loading configurations.");
    if (!configs) // Checks if the configuration pointer is valid.
    {
        NADIA_CORE.log("!! Nadia failed: configs pointer is null. !!\n");
        // return NULL;
    }

    // Allocates nadia_core_t.
    // nadia_core_t *core = (nadia_core_t *) malloc(sizeof(nadia_core_t));
    // NADIA_CORE.log(">> Nadia: Core allocation done.\n");

    // Initializes the library.
    NADIA_CORE.log(">> Nadia: Initializing SDL.\n");
    if (NADIA_BACKEND.init())
    {   // Displays a message and prevents memory leak.
        NADIA_CORE.log("! Nadia failed: Couldn't initialize backend !\n");
        // free(core);
        // return NULL;
    }
    NADIA_CORE.log(">> Nadia: success.\n");

    // If everything went fine, then the status is set to RUNNING.
    NADIA_CORE.state = NADIA_STATE_RUNNING;
    NADIA_CORE.log("Nadia is now running.\n\n");

    // return core;
}

// Destroys the logical environment.
void quit(void)
{
    NADIA_BACKEND.quit();
    // if (!c) return;
    if (NADIA_CORE.title) free(NADIA_CORE.title);
    // free(c);
}

// Returns the current state of Nadia.
int get_state(void)
{ return NADIA_CORE.state; }

/* Module: Hi-Res Timer. */
static uint64_t modern_get_ticks(void) {return SDL_GetTicks64(); }
static void modern_sleep(uint32_t ms) { SDL_Delay(ms); }

void modern_log(const char *message) { fprintf(stderr, message); }
void set_debug_mode(uint8_t status) { NADIA_CORE.debug_mode = status; }

// Delays execution in miliseconds.
void nadia_await(unsigned int ms)
{ NADIA_CORE.sleep_ms(ms); }

// Delays execution in seconds.
void nadia_await_seconds(unsigned int s)
{ NADIA_CORE.sleep_ms(s * 1000); }

int modern_poll_events(void *event)
{ return SDL_PollEvent((SDL_Event *) event); }

nadia_core_t NADIA_CORE = {
    .init = init,
    .quit = quit,
    .get_state = get_state,
    .get_ticks_ms = modern_get_ticks,
    .sleep_ms = modern_sleep,
    .log = modern_log,
    .set_debug_mode = set_debug_mode,
    .poll_events = modern_poll_events,
    .state = NADIA_STATE_INITIALIZING,
    .debug_mode = 0x00,
};
