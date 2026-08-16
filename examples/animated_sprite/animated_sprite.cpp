// Animated Sprites example.

// Sprite source:
// https://merakintsugi.itch.io/platformer-character-pack
// used files: idle.png, from idle.png and walk.png
// NOT INCLUDED IN THIS EXAMPLE, PLEASE DOWNLOAD AND LOCATE IT BY YOURSELF.

#define MON_SCREENSCALE    2
#define MON_TITLE       (char *) "ANIMATED SPRITES"
#define MON_SCREEN_W  320 * MON_SCREENSCALE
#define MON_SCREEN_H  200 * MON_SCREENSCALE
#define MON_FRAMERATE 60

#ifdef __DJGPP__

#include <allegro.h>
#include <stdio.h>
// #include <stdlib.h>
// #include <stdint.h>
// #include <math.h>

// game_t game;
// int frame, frame_counter = 0;
// BITMAP *sprite_buffer;

// int next;

int main(void)
{
    if (allegro_init() != 0) return EXIT_FAILURE;
    install_keyboard();
    // install_timer();

    if (set_gfx_mode(GFX_AUTODETECT, SCREEN_W, SCREEN_W, 0, 0) != 0)
    {
        set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
        allegro_message("Cannot set graphics mode: \r\n%s\r\n", allegro_error);
        return EXIT_FAILURE;
    }

    printf("El programa se ha ejecutado.");

    set_palette(desktop_palette);
    clear_to_color(screen, makecol(255, 255, 255));
    textout_centre_ex(screen, font, "Hello, world!", SCREEN_W / 2, SCREEN_H / 2, makecol(0,0,0), -1);

    readkey();

    return EXIT_SUCCESS;

    // char *img_locations[] = {"./idle.png", "./from idle.png", "./walk.png"};
    // char *img_names[] = {"idle", "from_idle", "walk"};

    // uint8_t img_count = (uint8_t) (sizeof(img_locations) / sizeof(char *));

    // img_t **images = (img_t **) malloc((uint8_t) sizeof(img_t *) * img_count);

    // for (int i = IDLE; i <= WALK; i++)
    //     images[i] = create_img_t(game.renderer, img_locations[i], img_names[i]);

    // // Since every image has different sprite dimensions, well...
    // uint8_t sprite_widths[3] = {46, 45, 45};
    // uint8_t sprite_heights[3] = {55, 58, 58};

    // animation_t **animations = (animation_t **) malloc(
    //     (int) ( sizeof(animation_t *) * img_count )
    // );

    // for (int i = IDLE; i <= WALK; i++)
    // {
    //     printf("Index: %d\n", i);
    //     int columns = images[i]->w / sprite_widths[i];
    //     int rows = images[i]->h / sprite_heights[i];
    //     int total_frames = columns * rows;

    //     printf("Total frames: %d\n", total_frames);

    //     animations[i] = create_animation_t(64, total_frames, images[i]->name);

    //     if (animations[i]) printf("Successfully created '%s' animation.\n", animations[i]->name);
    //     else
    //     {
    //         printf("Couldn't create animation with %d index.\n", i);
    //         return EXIT_FAILURE;
    //     }
    // }

    // sprite_t sprite(images[IDLE], sprite_widths[IDLE], sprite_heights[IDLE]);

    // sprite.position(
    //     (screen.w - sprite.get_width() * SCREENSCALE) / SCREENSCALE,
    //     (screen.h - sprite.get_height() * SCREENSCALE) / SCREENSCALE
    // );

    // sprite.iScale(SCREENSCALE);
}

END_OF_MAIN();

#else

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "defaults.h"

#include "init.h"
#include "graphics.h"
#include "input.h"

#include "strings.h"
#include "delta_t.h"

#define WINFLAGS    SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_INPUT_FOCUS | SDL_WINDOW_MOUSE_FOCUS

game_t game;
screen_t screen = {
    SCREEN_W, SCREEN_H,
    SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED
};

delta_t *delta = create_delta_t(FRAMERATE);

enum enum_animations { IDLE, FROM_IDLE, WALK };

mouse_t mouse;
keyboard_t clavier;

int main()
{
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest");

    init_everything(&game, TITLE, &screen, WINFLAGS, -1, DEFAULT_REND_FLAGS);

    char *img_locations[] = {"./idle.png", "./from idle.png", "./walk.png"};
    char *img_names[] = {"idle", "from_idle", "walk"};

    uint8_t img_count = (uint8_t) (sizeof(img_locations) / sizeof(char *));

    img_t **images = (img_t **) malloc((uint8_t) sizeof(img_t *) * img_count);

    for (int i = IDLE; i <= WALK; i++)
        images[i] = create_img_t(game.renderer, img_locations[i], img_names[i]);

    // Since every image has different sprite dimensions, well...
    uint8_t sprite_widths[3] = {46, 45, 45};
    uint8_t sprite_heights[3] = {55, 58, 58};

    animation_t **animations = (animation_t **) malloc(
        (int) ( sizeof(animation_t *) * img_count )
    );

    for (int i = IDLE; i <= WALK; i++)
    {
        printf("Index: %d\n", i);
        int columns = images[i]->w / sprite_widths[i];
        int rows = images[i]->h / sprite_heights[i];
        int total_frames = columns * rows;

        printf("Total frames: %d\n", total_frames);

        animations[i] = create_animation_t(64, total_frames, images[i]->name);

        if (animations[i]) printf("Successfully created '%s' animation.\n", animations[i]->name);
        else
        {
            printf("Couldn't create animation with %d index.\n", i);
            return EXIT_FAILURE;
        }
    }

    sprite_t sprite(images[IDLE], sprite_widths[IDLE], sprite_heights[IDLE]);

    sprite.position(
        (screen.w - sprite.get_width() * SCREENSCALE) / SCREENSCALE,
        (screen.h - sprite.get_height() * SCREENSCALE) / SCREENSCALE
    );

    sprite.iScale(SCREENSCALE);

    uint8_t animation_index = 0;
    uint8_t previous_animation_index = 0;

    uint8_t atlas_index = 0;
    uint8_t previous_atlas_index = 0;

    const uint8_t max_delay_ms = 96;
    const uint8_t min_delay_ms = 64;
    const float speed_change_factor = 0.08f;

    float current_speed_factor = 1.0f;
    float target_speed_factor = 1.0f;

    int8_t  dir[2] = {0, 0};

    bool    is_moving = false;
    bool    animation_ended = false;
    bool    transitioning = false;
    bool    running = true;

    while(running)
    {
        uint32_t current_time = SDL_GetTicks();
        delta->time_ms = current_time - delta->previous_time_ms;
        delta->previous_time_ms = current_time;

        if (delta->time_ms > 100) delta->time_ms = 16;
        if (delta->time_ms == 0) delta->time_ms = 1;

        // INPUT HANDLING
        clavier.state = (uint8_t*) SDL_GetKeyboardState(NULL);

        clavier.pressed = (
            clavier.state[SDL_SCANCODE_RIGHT]
            || clavier.state[SDL_SCANCODE_LEFT]
            || clavier.state[SDL_SCANCODE_X]
        ) ? true : false;

        while (SDL_PollEvent(&game.event))
        {
            if (game.event.type == SDL_QUIT) running = false;
        }

        dir[0] = 0;
        if (clavier.state[SDL_SCANCODE_RIGHT] && !clavier.state[SDL_SCANCODE_LEFT]) dir[0] = 1;
        if (!clavier.state[SDL_SCANCODE_RIGHT] && clavier.state[SDL_SCANCODE_LEFT]) dir[0] = -1;

        target_speed_factor = clavier.state[SDL_SCANCODE_X] ? 3.0f : 1.0f;

        // MAIN LOGIC
        is_moving = (dir[0] != 0);

        if (dir[0] == 1) sprite.flip_horizontally(true);    // FLips sprite.
        if (dir[0] == -1) sprite.flip_horizontally(false);  // Reverts flip.

        // Since delay animation was already precalculated and
        // transcurred time += delta
        // frame index = (transucrred time) / (total time)
        // the secondary option was to make delta time value lil bit bigger
        // 
        uint32_t adjusted_delta = (animation_index == 2)
            ? (uint32_t) (delta->time_ms * current_speed_factor)
            : delta->time_ms;

        animation_ended = update_animation(animations[animation_index], adjusted_delta);

        // Begins idle animation.
        if (animation_index != 0 && !is_moving)
        {
            is_moving = false;
            transitioning = false;
            animation_index = IDLE;

            if (animation_ended)
            {
                animations[IDLE]->frame_index = 0;
                animations[IDLE]->timer_ms = 0;
            }
        }

        // Walking animations
        if (is_moving)
        {
            // if the 
            current_speed_factor += (target_speed_factor - current_speed_factor) * speed_change_factor;
            animations[FROM_IDLE]->delay_ms = clavier.state[SDL_SCANCODE_X] ? min_delay_ms : max_delay_ms;

            // Begins from_transition animation.
            if (animation_index == IDLE && !transitioning)
            {
                animation_index = FROM_IDLE;
                transitioning = true;

                animations[FROM_IDLE]->frame_index = 0;
                animations[FROM_IDLE]->timer_ms = 0;
            }

            // Begins walk animation
            if (transitioning && animation_ended)
            {
                animation_index = WALK;
                transitioning = false;

                animations[WALK]->frame_index = 0;
                animations[WALK]->timer_ms = 0;
            }
        }

        // Checks if the animation has changed.
        if (animation_index != previous_animation_index)
        {
            previous_animation_index = animation_index;
            sprite.set_image(images[animation_index]);
            sprite.dimensions(sprite_widths[animation_index], sprite_heights[animation_index]);
        }

        sprite.set_frame_by_index(animations[animation_index]->frame_index);

        SDL_SetRenderDrawColor(game.renderer, 0xf4, 0xf4, 0xf4, 0xff);
        SDL_RenderClear(game.renderer);
        sprite.render(game.renderer);
        SDL_RenderPresent(game.renderer);

        uint32_t elapsed = SDL_GetTicks() - current_time;
        dt_delay(elapsed, delta->ms_framerate_target);
    }

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

#endif
