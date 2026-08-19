
#include <nadia.h>

#define FPS_TARGET 60
#define FPS_TARGET_MS (int) (1000 / FPS_TARGET_MS)

void main(void)
{
    config_t *configs = load_default_configs();

    core_t *application = nadia_init();
    if (!application || !nadia_graphics_init(application, "SPRITE", configs))
        return EXIT_FAILURE;

    delta_t delta_time; memset(&delta_time, 0, sizeof(delta_t));

    while (nadia_state(application) == STATE_RUNNING)
    {
        delta_time.previous = delta_time.current;
        delta_time.start = delta_store_time();
    
        nadia_poll_events(application);

        nadia_clear_framebuffer(application, 0xFFF4F4F4);
        nadia_present();

        delta_time.end = delta_store_time();

        delta_time.elapsed = delta_time.end - delta_time.start;
        delta_time.current = delta_time.elapsed / FPS_TARGET_MS;
        nadia_await(16);
    }

    nadia_quit(application)
    return EXIT_SUCCESS;
}
