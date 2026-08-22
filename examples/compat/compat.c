#include <stdio.h>
#include <stdlib.h>

#include <nadia.h>
#include <graphics.h>

int main()
{
    config_t *configs = load_default_configs();

    core_t *application = nadia_init(configs);
    if (!application || !nadia_graphics_init(application, "COMPAT", configs))
        return EXIT_FAILURE;

    while (nadia_state(application) == STATE_RUNNING)
    {
        nadia_poll_events(application);

        nadia_clear_framebuffer(application, 0xFFF4F4F4);
        nadia_present(application);

        nadia_await(16);
    }

    nadia_quit(application);

    return EXIT_SUCCESS;
}
