// old/nadia.c
#include <nadia.h>

#include <allegro.h>
#include <stdlib.h>
#include <stdio.h>

// Initializes the logical environment.
static void init(config_t *configs)
{
    // nadia_config_t was unused for setting up a logical environment in Allegro.
    (void) configs;
    // setbuf(stderr, NULL);
    // setbuf(stdout, NULL);

    NADIA_CORE.log("Nadia is starting...\n");

    // Allocates nadia_core_t.
    // NADIA_CORE = (nadia_core_t *) malloc(sizeof(nadia_core_t));
    // NADIA_CORE.log(">> Nadia: Core allocation done.%p\n", (void*)core);

    // Initializes the library.
    NADIA_CORE.log(">> Nadia: Initializing Allegro.\n");
    if (NADIA_BACKEND.init() != 0)
    {   // Displays a message and prevents memory leak.
        NADIA_CORE.log("! Nadia failed !\n");
        // return NULL;
    }
    NADIA_CORE.log(">> Nadia: success.\n");

    // If everything went fine, then the status is set to RUNNING.
    NADIA_CORE.state = NADIA_STATE_RUNNING;
    NADIA_CORE.log("Nadia is now running.\n\n");
}

// Destroys the logical environment.
static void quit(void)
{
    NADIA_CORE.backend_quit();
    // if (!NADIA_CORE) return;
    if (NADIA_CORE.title) free(NADIA_CORE.title);
    // free(c);
}

// Returns the current state of Nadia.
static int get_state(void)
{ return NADIA_CORE->state; }

static uint64_t old_get_ticks(void) { return (uint64_t) (allegro_get_time() * 1000.0); }
static void old_sleep(uint32_t ms) { rest(ms); }

static void old_log(const char *msg) { allegro_message("%s", msg); }
static void old_poll_events(void *event) { return -1; }

nadia_core_t NADIA_CORE = {
    .init = init,
    .quit = quit,
    .get_state = get_state,
    .get_ticks_ms = old_get_ticks,
    .sleep_ms = old_sleep,
    .log = old_log,
    .poll_events = old_poll_events
};
