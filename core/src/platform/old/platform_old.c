#include <platform_api.h>
#include <allegro.h>

static uint64_t old_get_ticks(void) { return (uint64_t) (allegro_get_time() * 1000.0); }
static void old_sleep(uint32_t ms) { rest(ms); }
static void old_log(const char *msg) { allegro_message("%s", msg); }
static void old_poll_events(void *core_state) { return; }

// MS-DOS doesn't have windows.
static void *old_create_window(const char *title, display_t *area, unsigned int flags)
{ (void) title; (void) area; (void) flags; return NULL; }

static void old_destroy_window(void *handle) { (void) handle; return; }

platform_api_t NADIA_PLATFORM = {
    .get_ticks_ms = old_get_ticks,
    .sleep_ms = old_sleep,
    .log = old_log,
    .poll_events = old_poll_events,
    .create_window = old_create_window,
    .destroy_window = old_destroy_window
};
