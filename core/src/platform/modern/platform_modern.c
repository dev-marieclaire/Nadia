#include <platform_api.h>
#include <graphics/graphics.h>
#include <SDL2/SDL.h>

static uint64_t modern_get_ticks(void) {return SDL_GetTicks64(); }
static void modern_sleep(uint32_t ms) { SDL_Delay(ms); }
static void modern_log(const char *msg) { fprintf(stderr, "%s\n", msg); }

int modern_poll_events(void *event)
{ return SDL_PollEvent((SDL_Event *) event); }

nadia_window_t *modern_create_window(const char *title, display_t *area, unsigned int flags)
{
    fprintf(stderr, ">> Nadia: Requested window values: title=%s x=%u y=%u w=%u h=%u flags=%u\n",
            title ? title : " null", area->x, area->y, area->w, area->h, flags);
    fflush(stderr);

    unsigned int _flags = flags;

    if (area->x == 0)
    {
        fprintf(stderr, "## Nadia warning: Missing initial x position for window. Using default. ##\n");
        area->x = SDL_WINDOWPOS_CENTERED;
    }
    if (area->y == 0)
    {
        fprintf(stderr, "## Nadia warning: Missing initial y position for window. Using default. ##\n");
        area->y = SDL_WINDOWPOS_CENTERED;
    }
    if (area->w == 0)
    {
        fprintf(stderr, "## Nadia warning: Missing initial width for window. Using default. ##\n");
        area->w = DEFAULT_DISPLAY_WIDTH;
    }
    if (area->h == 0)
    {
        fprintf(stderr, "## Nadia warning: Missing initial height for window. Using default. ##\n");
        area->h = DEFAULT_DISPLAY_HEIGHT;
    }
    if (flags == 0)
    {
        fprintf(stderr, "## Nadia warning: Missing initial window flags. Using default. ##\n");
        _flags = DEFAULT_WINFLAGS;
    }

    SDL_Window *win = SDL_CreateWindow(title, (int) area->x, (int) area->y, (int) area->w, (int) area->h, _flags);
    fprintf(stderr, ">> Nadia: window allocated at %p\n", (void*)win);
    fflush(stderr);

    if (!win)
    {
        fprintf(stderr, "! Nadia failed: Couldn't create window !\n%s", SDL_GetError());
        fflush(stderr);
        return NULL;
    }

    return (nadia_window_t *) win;
}

void modern_destroy_window(void *handle)
{ SDL_DestroyWindow((SDL_Window *) handle); }

platform_api_t NADIA_PLATFORM = {
    .get_ticks_ms = modern_get_ticks,
    .sleep_ms = modern_sleep,
    .log = modern_log,
    .poll_events = modern_poll_events,
    .create_window = modern_create_window,
    .destroy_window = modern_destroy_window
};
