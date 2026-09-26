// platform/modern/graphics.c
#include <nadia.h>
#include <platform/api.h>

#include <graphics/graphics.h>
#include "priv_modern.h"

/* CONTEXT CREATION */

// Creates a window. Defaults are read from the given config.
static nadia_window_t *modern_create_window(
    const config_t *cfg,
    const char *title,
    display_t *area,
    unsigned int flags
)
{
    // Starts from the config's defaults, then applies per-call overrides.
    int x = NADIA_CONFIG.get_display_x(cfg);
    int y = NADIA_CONFIG.get_display_y(cfg);
    int w = NADIA_CONFIG.get_display_w(cfg);
    int h = NADIA_CONFIG.get_display_h(cfg);

    if (area)
    {
        if (area->x == 0) NADIA_LOG_WARN("Missing initial x position for window. Using default.\n");
        else x = area->x;

        if (area->y == 0) NADIA_LOG_WARN("Missing initial y position for window. Using default.\n");
        else y = area->y;

        if (area->w == 0) NADIA_LOG_WARN("Missing initial width for window. Using default.\n");
        else w = (int) area->w;

        if (area->h == 0) NADIA_LOG_WARN("Missing initial height for window. Using default.\n");
        else h = (int) area->h;
    }
    else
    {
        NADIA_LOG_WARN("Missing window configuration. Using default.\n");
    }

    if (flags == 0)
    {
        NADIA_LOG_WARN("Missing initial window flags. Using default.\n");
        flags = NADIA_CONFIG.get_window_flags(cfg);
    }

    const char *final_title = title ? title : NADIA_CONFIG.get_title(cfg);
    if (!final_title) final_title = "APPLICATION";

    SDL_Window *win = SDL_CreateWindow(final_title, x, y, w, h, (int) flags);
    NADIA_LOG_DEBUG("Window allocated at %p\n", (void *) win);

    if (!win)
    {
        NADIA_LOG_ERROR("Couldn't create window: %s\n", SDL_GetError());
        return NULL;
    }

    // Wraps the SDL window so it can travel through the public header opaquely.
    nadia_window_t *wrapper = malloc(sizeof(*wrapper));
    if (!wrapper)
    {
        SDL_DestroyWindow(win);
        return NULL;
    }
    wrapper->window = win;
    return wrapper;
}

// Destroys a window.
void modern_destroy_window(nadia_window_t *handle)
{
    if (!handle) return;
    SDL_DestroyWindow(handle->window);
    free(handle);
}

// Creates and configures a new graphical context.
static nadia_graphics_context_t *modern_create_context(const nadia_graphics_context_desc_t *desc)
{
    NADIA_LOG_INFO("Nadia is initializing the graphical environment...\n");

    // Allocates the struct for the graphics context.
    nadia_graphics_context_t *ctx = calloc(1, sizeof(*ctx));
    if (!ctx)
    {
        NADIA_LOG_FATAL("Couldn't allocate graphical context.\n");
        return NULL;
    }

    // Resolves the config for this context.
    // - If the caller supplied one, use it; take ownership only if asked.
    // - Otherwise, create a private default config owned by this context.
    if (desc && desc->config)
    {
        ctx->config      = desc->config;
        ctx->owns_config = desc->take_ownership ? 1 : 0;
    }
    else
    {
        ctx->config      = NADIA_CONFIG.load_defaults();
        ctx->owns_config = 1;
        if (!ctx->config)
        {
            NADIA_LOG_FATAL("Couldn't load default configuration.\n");
            free(ctx);
            return NULL;
        }
    }

    // Gets and sets the configured display.
    NADIA_LOG_INFO(">> Nadia: Creating display.\n");
    ctx->display = NADIA_CONFIG.get_display(ctx->config);
    if (!ctx->display)
    {
        NADIA_LOG_ERROR("Display is null.\n");
        if (ctx->owns_config) free_config(ctx->config);
        free(ctx);
        return NULL;
    }
    NADIA_LOG_INFO(NADIA_SUCCESS_MSG);

    // Creates window.
    NADIA_LOG_INFO(">> Nadia: Creating window.\n");

    const char   *title = (desc && desc->title) ? desc->title : NULL;
    display_t    *area  = (desc && desc->area)  ? desc->area  : NULL;
    unsigned int  flags = (desc && desc->flags) ? desc->flags : 0;

    ctx->window = NADIA_GRAPHICS.backend->create_window(ctx->config, title, area, flags);
    if (!ctx->window)
    {
        NADIA_LOG_ERROR("Couldn't initialize window.\n");
        if (ctx->owns_config) free_config(ctx->config);
        free(ctx);
        return NULL;
    }
    NADIA_LOG_INFO(NADIA_SUCCESS_MSG);

    // Creates framebuffer (renderer).
    NADIA_LOG_INFO(">> Nadia: Creating framebuffer.\n");

    SDL_Renderer *renderer = SDL_CreateRenderer(
        ctx->window->window,
        -1,
        NADIA_CONFIG.get_renderer_flags(ctx->config)
    );
    if (!renderer)
    {
        NADIA_LOG_ERROR("Couldn't create renderer: %s\n", SDL_GetError());
        NADIA_GRAPHICS.backend->destroy_window(ctx->window);
        if (ctx->owns_config) free_config(ctx->config);
        free(ctx);
        return NULL;
    }

    // Wraps the SDL renderer.
    nadia_renderer_t *wrapper = malloc(sizeof(*wrapper));
    if (!wrapper)
    {
        SDL_DestroyRenderer(renderer);
        NADIA_GRAPHICS.backend->destroy_window(ctx->window);
        if (ctx->owns_config) free_config(ctx->config);
        free(ctx);
        return NULL;
    }
    wrapper->renderer = renderer;
    ctx->renderer = wrapper;

    NADIA_LOG_INFO(NADIA_SUCCESS_MSG);

    NADIA_LOG_INFO(">> Nadia: Graphical environment is now ready.\n");

    return ctx;
}

// Releases a graphical context and everything it owns.
static void modern_quit(nadia_graphics_context_t *ctx)
{
    if (!ctx) return;

    if (ctx->renderer)
    {
        SDL_DestroyRenderer(ctx->renderer->renderer);
        free(ctx->renderer);
        ctx->renderer = NULL;
    }

    if (ctx->window)
    {
        SDL_DestroyWindow(ctx->window->window);
        free(ctx->window);
        ctx->window = NULL;
    }

    // Only frees the config if this context owns it. A shared config is
    // left alone so other contexts can keep using it.
    if (ctx->owns_config && ctx->config)
    {
        free_config(ctx->config);
        ctx->config = NULL;
    }

    free(ctx);
}

/* NADIA GRAPHICS */

// Clears display to a color.
static void modern_clear_display(nadia_graphics_context_t *ctx, unsigned int color)
{
    if (!ctx || !ctx->renderer) return;

    SDL_SetRenderDrawColor(
        ctx->renderer->renderer,
        (uint8_t) (color>>16)&0xFF,
        (uint8_t) (color>>8)&0xFF,
        (uint8_t)  color&0xFF,
        (uint8_t) (color>>24)&0xFF
    );
    SDL_RenderClear(ctx->renderer->renderer);
}

// Blits to the display.
static void modern_present(nadia_graphics_context_t *ctx)
{
    if (!ctx || !ctx->renderer) return;
    SDL_RenderPresent(ctx->renderer->renderer);
}

/* TEXTURING */

// Loads a texture.
static nadia_texture_t *modern_load_texture(const char *src, nadia_renderer_t *dest)
{
    if (!dest)
    {
        NADIA_LOG_ERROR("Cannot load texture '%s': renderer is NULL.\n", src ? src : "(null)");
        return NULL;
    }

    SDL_Surface *data = IMG_Load(src); // Turns out this method automatically detects the format.
    if (!data)
    {
        NADIA_LOG_ERROR("Failed to load '%s': %s\n", src ? src : "(null)", IMG_GetError());
        return NULL;
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(dest->renderer, data);
    SDL_FreeSurface(data);

    if (!texture)
    {
        NADIA_LOG_ERROR("Couldn't create texture from '%s': %s\n", src ? src : "(null)", SDL_GetError());
        return NULL;
    }

    // Wraps the SDL texture so it can travel through the public header opaquely.
    nadia_texture_t *wrapper = malloc(sizeof(*wrapper));
    if (!wrapper)
    {
        SDL_DestroyTexture(texture);
        return NULL;
    }
    wrapper->texture = texture;
    return wrapper;
}

// Releases a texture.
static void modern_free_texture(nadia_texture_t *texture)
{
    if (!texture) return;
    SDL_DestroyTexture(texture->texture);
    free(texture);
}

/* BACKEND VTABLE */

nadia_graphics_backend_t MODERN_GRAPHICS_BACKEND = {
    .create_context = modern_create_context,
    .quit           = modern_quit,
    .clear_display  = modern_clear_display,
    .present        = modern_present,
    .load_texture   = modern_load_texture,
    .free_texture   = modern_free_texture,
    .create_window  = modern_create_window,
    .destroy_window = modern_destroy_window
};

nadia_graphics_t NADIA_GRAPHICS = {
    .backend   = &MODERN_GRAPHICS_BACKEND,
    .instances = NULL,
    .size      = 0,
    .capacity  = 0
};

/* PUBLIC API */

// Resolves an index into a graphical context.
nadia_graphics_context_t *nadia_graphics_resolve(int index)
{
    if (index < 0 || index >= NADIA_GRAPHICS.size) return NULL;
    return NADIA_GRAPHICS.instances[index];
}

// Creates a new graphical context and returns its index, or -1 on failure.
int nadia_graphics_create_context(const nadia_graphics_context_desc_t *desc)
{
    nadia_graphics_context_t *ctx = NADIA_GRAPHICS.backend->create_context(desc);
    if (!ctx) return -1;

    // Reuses a hole left by a previously destroyed context.
    for (int i = 0; i < NADIA_GRAPHICS.size; i++)
    {
        if (NADIA_GRAPHICS.instances[i] == NULL)
        {
            NADIA_GRAPHICS.instances[i] = ctx;
            return i;
        }
    }

    // Grows the array if every slot is occupied.
    if (NADIA_GRAPHICS.size == NADIA_GRAPHICS.capacity)
    {
        int new_capacity = NADIA_GRAPHICS.capacity ? NADIA_GRAPHICS.capacity * 2 : 4;
        nadia_graphics_context_t **grown = realloc(
            NADIA_GRAPHICS.instances,
            new_capacity * sizeof(*grown)
        );
        if (!grown)
        {
            NADIA_LOG_ERROR("Couldn't grow context table to %d slots.\n", new_capacity);
            NADIA_GRAPHICS.backend->quit(ctx);
            return -1;
        }
        NADIA_GRAPHICS.instances = grown;
        NADIA_GRAPHICS.capacity  = new_capacity;
    }

    NADIA_GRAPHICS.instances[NADIA_GRAPHICS.size] = ctx;
    return NADIA_GRAPHICS.size++;
}

// Destroys the context at the given index, leaving a reusable hole.
void nadia_graphics_quit_context(int index)
{
    nadia_graphics_context_t *ctx = nadia_graphics_resolve(index);
    if (!ctx) return;

    NADIA_GRAPHICS.backend->quit(ctx);
    NADIA_GRAPHICS.instances[index] = NULL;
}

// Clears the given context's display to a color.
void nadia_graphics_clear_display(int index, unsigned int color)
{
    nadia_graphics_context_t *ctx = nadia_graphics_resolve(index);
    if (!ctx) return;
    NADIA_GRAPHICS.backend->clear_display(ctx, color);
}

// Presents the given context.
void nadia_graphics_present(int index)
{
    nadia_graphics_context_t *ctx = nadia_graphics_resolve(index);
    if (!ctx) return;
    NADIA_GRAPHICS.backend->present(ctx);
}

// Loads a texture for the given context.
nadia_texture_t *nadia_graphics_load_texture(int index, const char *src)
{
    nadia_graphics_context_t *ctx = nadia_graphics_resolve(index);
    if (!ctx) return NULL;
    return NADIA_GRAPHICS.backend->load_texture(src, ctx->renderer);
}

// Releases a texture previously created by nadia_graphics_load_texture.
void nadia_graphics_free_texture(nadia_texture_t *texture)
{
    if (!texture) return;
    NADIA_GRAPHICS.backend->free_texture(texture);
}
