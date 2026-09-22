#include <platform/api.h>
#include <graphics/graphics.h>
#include <SDL2/SDL.h>

/* BACKEND */
static int modern_backend_init(void)
{
    if (SDL_Init(NADIA_CONFIG.get_backend_flags()) < 0)
    {
        fprintf(stderr, "SDL_Init failed: %s\n", SDL_GetError());
        return -1;
    }

    return 0;
}

static int modern_init_timer(void)
{
    if (SDL_InitSubSystem(SDL_INIT_TIMER) > 0)
    {
        fprintf(stderr, "SDL_Init failed: %s\n", SDL_GetError());
        return -1;
    }

    return 0;
}

static int modern_init_video(const char *driver_name)
{
    if (SDL_VideoInit(driver_name) < 0)
    {
        fprintf(stderr, "SDL_Init failed: %s\n", SDL_GetError());
        return -1;
    }

    return 0;
}

static int modern_init_image(void)
{
    if (IMG_Init(NADIA_CONFIG.get_image_flags()) > 0)
    {
        fprintf(stderr, "SDL_Init failed: %s\n", SDL_GetError());
        return -1;
    }

    return 0;
}

static void modern_backend_quit(void) { SDL_Quit(); }

/* NADIA GRAPHICS */
static nadia_texture_t *modern_load_texture(const char *src, nadia_renderer_t *dest)
{
    if (!dest)
    {
        NADIA_CORE.log("Renderer is NULL.\n");
        return NULL;
    }

    SDL_Surface *data = IMG_Load(src); // Turns out this method automatically detects the format.
    if (!data)
    {
        NADIA_CORE.log("Failed to load ");
        NADIA_CORE.log(src);
        NADIA_CORE.log(IMG_GetError());
        return NULL;
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface((SDL_Renderer *) dest, data);
    if (!texture)
    {
        NADIA_CORE.log("Couldn't create texture: ");
        NADIA_CORE.log(SDL_GetError());
        SDL_FreeSurface(data);
        return NULL;
    }

    SDL_FreeSurface(data);

    return (nadia_texture_t *) texture;
}

nadia_window_t *modern_create_window(const char *title, display_t *area, unsigned int flags)
{
    if (area)
    {
        if (area->x == 0) fprintf(stderr, "## Nadia warning: Missing initial x position for window. Using default. ##\n");
        if (area->y == 0) fprintf(stderr, "## Nadia warning: Missing initial y position for window. Using default. ##\n");

        if (area->w == 0) fprintf(stderr, "## Nadia warning: Missing initial width for window. Using default. ##\n");
        if (area->h == 0) fprintf(stderr, "## Nadia warning: Missing initial height for window. Using default. ##\n");
    }
    else fprintf(stderr, "## Nadia warning: Missing window configuration. Using default. ##\n");

    if (flags == 0) fprintf(stderr, "## Nadia warning: Missing initial window flags. Using default. ##\n");

    nadia_window_t *win = (nadia_window_t *) SDL_CreateWindow(
        (title ? title : NADIA_CONFIG.get_title()),
        (int)(area->x != 0 ? area->x : NADIA_CONFIG.get_display_x()),
        (int)(area->y != 0 ? area->y : NADIA_CONFIG.get_display_y()),
        (int)(area->w != 0 ? area->w : NADIA_CONFIG.get_display_w()),
        (int)(area->h != 0 ? area->h : NADIA_CONFIG.get_display_h()),
        (int)(flags != 0 ? flags : NADIA_CONFIG.get_window_flags())
    );
    fprintf(stderr, ">> Nadia: window allocated at %p\n", (void*)win); fflush(stderr);

    if (!win)
    {
        fprintf(stderr, "! Nadia failed: Couldn't create window !\n%s", SDL_GetError()); fflush(stderr);
        NADIA_GFX.destroy_window(win);
        return NULL;
    }

    return win;
}

void modern_destroy_window(nadia_window_t *handle)
{ SDL_DestroyWindow((SDL_Window *) handle); }

nadia_backend_t NADIA_BACKEND = {
    .init = modern_backend_init,
    .init_timer = modern_init_timer,
    .init_video = modern_init_video,
    .init_image = modern_init_image,
    .quit = modern_backend_quit
};

nadia_gfxapi_t NADIA_GRAPHICS = {
    .load_texture = modern_load_texture,
    .create_window = modern_create_window,
    .destroy_window = modern_destroy_window
};
