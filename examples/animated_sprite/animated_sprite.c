#include <nadia.h>
#include <graphics/graphics.h>
#include <graphics/img.h>

#include <stdlib.h>
#include <stdio.h>

int main(void)
{
    config_t *config = load_default_configs();

    core_t *application = nadia_init(config);
    nadia_graphics_t *graphics = nadia_graphics_init(config);

    if (!application || !graphics)
        return EXIT_FAILURE;

    img_t *image = create_image(graphics->renderer, "dither.bmp", "Parlements de Londres");

    delta_t delta_time;
    delta_time_init(&delta_time, 60);

    while (nadia_state(application) == STATE_RUNNING)
    {
        // delta_time.start = delta_store_time();
        nadia_poll_events(application);

        nadia_clear_display(graphics, 0xFFF4F4F4);

        nadia_blit_image(image, graphics);

        nadia_graphics_present(graphics);
        // delta_time.end = delta_store_time();

        // nadia_await(delta_time.end - delta_time.start);
    }

    nadia_graphics_quit(graphics);
    nadia_quit(application);

    return EXIT_SUCCESS;
}
