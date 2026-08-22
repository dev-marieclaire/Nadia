// sprite example.
#include "nadia.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#define FPS_TARGET 60
#define FPS_TARGET_MS (int) (1000 / FPS_TARGET)

int main(void)
{
    config_t *configs = load_default_configs();

    core_t *application = nadia_init(configs);
    if (!application || !nadia_graphics_init(application, "SPRITE", configs))
        return EXIT_FAILURE;

    delta_t delta_time;
    delta_time_init(&delta_time, FPS_TARGET_MS);

    while (nadia_state(application) == STATE_RUNNING)
    {
        // delta_time.previous = delta_time.current;
        delta_time.start = delta_store_time();
    
        nadia_poll_events(application);

        nadia_clear_framebuffer(application, 0xFFF4F4F4);
        nadia_present(application);

        // delta_time.end = delta_store_time();
        delta_time.current = (delta_time.end - delta_time.start) / FPS_TARGET_MS;

        if (delta_time.current < FPS_TARGET_MS)
            nadia_await(FPS_TARGET_MS - delta_time.current);
    }

    nadia_quit(application);
    return EXIT_SUCCESS;
}
