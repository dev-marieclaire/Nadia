// Sprite source:
// https://merakintsugi.itch.io/platformer-character-pack
// used file: idle.png
// NOT INCLUDED IN THIS EXAMPLE, MANUALLY DOWNLOAD AND LOCATE IT.

// Animated Sprites example.

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "init.h"

#include "screen.h"
#include "input.h"

#include "strings.h"
#include "img_t.h"
#include "sprite.h"

#include "animation_t.h"
#include "delta_t.h"

#define SCALE 2

int main()
{
    game_t game;

    img_t **images = (img_t **) malloc(sizeof(img_t *) * 3);

    mouse_t mouse;
    keyboard_t clavier;

    // Prevents accidental flags by setting every value to 0.
    memset(&game, 0, sizeof(game));
    game.title = NULL;

    game.winflags = SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_INPUT_FOCUS | SDL_WINDOW_MOUSE_FOCUS;

    // Must be defined before creating a window and renderer.
    const int base_win_w = game.win_w = 320 * SCALE;
    const int base_win_h = game.win_h = 200 * SCALE;

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest");

    game.title = string("ANIMATED SPRITES");

    init_everything(&game);

    images[0] = create_img_t(game.renderer, "./idle.png", "idle");
    images[1] = create_img_t(game.renderer, "./from idle.png", "from_idle");
    images[2] = create_img_t(game.renderer, "./walk.png", "walk");

    printf("Texture size: %d\n", (int) sizeof(images[0]->texture));
    printf("Struct size: %d\n", (int) sizeof(images));

    const uint8_t animations_w[3] = {46, 45, 45};
    const uint8_t animations_h[3] = {55, 58, 58};

    sprite_t sprite(images[0], animations_w[0], animations_h[0]);

    sprite.position(
        (game.win_w - sprite.getFrame().w * SCALE) / SCALE,
        (game.win_h - sprite.getFrame().h * SCALE) / SCALE
    );

    sprite.iScale(SCALE);

    int columns = sprite.getAtlas()->w / animations_w[0];
    int rows = sprite.getAtlas()->h / animations_h[0];
    int total_frames = columns * rows;

    printf("Total frames: %d\n", total_frames);

    animation_t *idle = create_animation_t(64, total_frames, "idle");

    columns = images[1]->w / animations_w[1];
    rows = images[1]->h / animations_h[1];
    total_frames = columns * rows;

    printf("Total frames: %d\n", total_frames);

    animation_t *from_idle = create_animation_t(24, total_frames, "from_idle");

    columns = images[2]->w / animations_w[2];
    rows = images[2]->h / animations_h[2];
    total_frames = columns * rows;

    printf("Total frames: %d\n", total_frames);

    animation_t *walk = create_animation_t(64, total_frames, "walk");

    animation_t **animations = (animation_t **) malloc(sizeof(animation_t *) * 3);
    animations[0] = idle;
    animations[1] = from_idle;
    animations[2] = walk;

    bool running = true;

    delta_t *delta = create_delta_t(60);

    int animation_index = 0;
    int previous_animation_index = 0;
    int atlas_index = 0;
    int previous_atlas_index = 0;

    bool animation_ended = false;
    bool transitioning = false;

    const uint8_t max_delay_ms = 64;
    const uint8_t min_delay_ms = 32;
    float current_walk_delay = 64.0f;
    float target_walk_delay = 64.0f;
    float previous_walk_delay = 64.0f;
    float current_speed_factor = 1.0f;
    float target_speed_factor = 1.0f;
    const float SMOOTH_FACTOR = 0.08f;

    short int dir[2] = {0, 0};

    int previous_dir = 0;

    while(running)
    {
        uint32_t current_time = SDL_GetTicks();
        delta->time_ms = current_time - delta->previous_time_ms;
        delta->previous_time_ms = current_time;

        if (delta->time_ms > 100) delta->time_ms = 16;
        if (delta->time_ms == 0) delta->time_ms = 1;

        clavier.state = (uint8_t*) SDL_GetKeyboardState(NULL);

        while (SDL_PollEvent(&game.event))
        {
            if (game.event.type == SDL_QUIT) running = false;
        }

        clavier.pressed = (
            clavier.state[SDL_SCANCODE_RIGHT]
            || clavier.state[SDL_SCANCODE_LEFT]
            || clavier.state[SDL_SCANCODE_X]
        ) ? true : false;

        if (!clavier.state[SDL_SCANCODE_RIGHT] && !clavier.state[SDL_SCANCODE_LEFT]) dir[0] = 0;
        if (clavier.state[SDL_SCANCODE_RIGHT] && !clavier.state[SDL_SCANCODE_LEFT]) dir[0] = 1;
        else if (!clavier.state[SDL_SCANCODE_RIGHT] && clavier.state[SDL_SCANCODE_LEFT]) dir[0] = -1;

        // FLips.
        if (dir[0] == 1) sprite.flip_horizontally(true);
        // Reverts flip.
        else if (dir[0] == -1) sprite.flip_horizontally(false);

        bool is_moving = (dir[0] != 0);

        target_speed_factor = clavier.state[SDL_SCANCODE_X] ? 3.0f : 1.0f;
        current_speed_factor += (target_speed_factor - current_speed_factor) * SMOOTH_FACTOR;

        animations[1]->delay_ms = clavier.state[SDL_SCANCODE_X] ? 64 : 96;

        if (animation_index == 0 && is_moving && !transitioning)
        {
            animation_index = 1;
            transitioning = true;
            animations[1]->frame_index = 0;
            animations[1]->timer_ms = 0;
        }

        if (animation_index != 0 && !is_moving && !transitioning)
        {
            animation_index = 0;
            animations[0]->frame_index = 0;
            animations[0]->timer_ms = 0;
        }

        if (transitioning && !is_moving)
        {
            animation_index = 0;
            transitioning = false;
            animations[0]->frame_index = 0;
            animations[0]->timer_ms = 0;
        }

        // printf("Animation index: %d\n", animation_index);

        uint32_t adjusted_delta = (animation_index == 2)
            ? (uint32_t) (delta->time_ms * current_speed_factor)
            : delta->time_ms;

        animation_ended = update_animation(animations[animation_index], adjusted_delta);
        
        if (transitioning && animation_ended)
        {
            animation_index = 2;
            transitioning = false;
            animations[2]->frame_index = 0;
            animations[2]->timer_ms = 0;
        }

        if (animation_index != previous_animation_index)
        {
            previous_animation_index = animation_index;
            sprite.setAtlas(images[animation_index]);
            sprite.setClipDimensions(animations_w[animation_index], animations_h[animation_index]);
        }

        sprite.set_frame_by_index(animations[animation_index]->frame_index);

        if (is_moving) previous_dir = dir[0];

        SDL_SetRenderDrawColor(game.renderer, 0xf4, 0xf4, 0xf4, 0xff);
        SDL_RenderClear(game.renderer);
        sprite.render(game.renderer);
        SDL_RenderPresent(game.renderer);

        uint32_t elapsed = SDL_GetTicks() - current_time;
        dt_delay(elapsed, delta->ms_framerate_target);
    }

    free(delta);
    free(idle);
    free(from_idle);
    free(walk);

    for (int i = 0; i < (int) (sizeof(images) / sizeof(img_t)); i++)
        free_img_t(images[i]);
    for (int i = 0; i < (int) (sizeof(animations) / sizeof(animation_t)); i++)
        free(animations[i]);

    free(game.title);

    SDL_DestroyRenderer(game.renderer);
    SDL_DestroyWindow(game.window);

    IMG_Quit();
    SDL_Quit();

    return EXIT_SUCCESS;
}