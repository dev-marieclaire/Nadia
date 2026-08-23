#include <stdio.h>
#include <stdlib.h>

#include <nadia.h>
#include <graphics.h>

int main()
{
    config_t *configs = load_default_configs();

    core_t *application = nadia_init(configs);
    nadia_graphics_t *graphics = nadia_graphics_init(configs);

    if (!application || !graphics)
        return EXIT_FAILURE;

    while (nadia_state(application) == STATE_RUNNING)
    {
        nadia_poll_events(application);

        nadia_clear_display(graphics, 0xFFF4F4F4);
        nadia_graphics_present(graphics);

        nadia_await(16);
    }

    nadia_graphics_quit(graphics);
    nadia_quit(application);

    return EXIT_SUCCESS;
}
