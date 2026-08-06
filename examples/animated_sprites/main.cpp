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
#include "clock_t.h"

int main()
{
    game_t game;
    img_t *sheet;

    mouse_t mouse;
    keyboard_t clavier; // Clavier is keyboard in French, it looks and sounds cooler imo.

    // Prevents accidental flags by setting every value to 0.
    memset(&game, 0, sizeof(game));
    game.title = NULL;

    game.winflags = SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_INPUT_FOCUS | SDL_WINDOW_MOUSE_FOCUS;

    // Must be defined before creating a window and renderer.
    const int base_win_w = game.win_w = 320 << 1;
    const int base_win_h = game.win_h = 200 << 1;

    game.title = string("ANIMATED SPRITES");
    
    init_everything(&game);

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest");

    game.framerate_target = 60;
    petite_clock_t *clock = create_clock_t(game.framerate_target);

    sheet = create_img_t(game.renderer, "./idle.png", "idle");

    const uint8_t idle_w = 46;
    const uint8_t idle_h = 55;

    sprite_t sprite(sheet, idle_w, idle_h);

    sprite.position(
        (game.win_w - (sprite.getFrame().w << 1)) >> 1,
        (game.win_h - (sprite.getFrame().h << 1)) >> 1
    );

    sprite.iScale(2);

    printf("After construction: clip=(%d,%d %dx%d)\n", 
       sprite.getClipFrame().x, sprite.getClipFrame().y,
       sprite.getClipFrame().w, sprite.getClipFrame().h);
    
    printf("After construction: area=(%d,%d %dx%d)\n", 
       sprite.getFrame().x, sprite.getFrame().y,
       sprite.getFrame().w, sprite.getFrame().h);

    int columns = sprite.getAtlas()->area.w / sprite.getClipFrame().w;
    int rows = sprite.getAtlas()->area.h / sprite.getClipFrame().h;
    int total_frames = columns * rows;

    printf("Total frames: %d\n", total_frames);

    animation_t *idle = create_animation_t(64.0f, total_frames, "idle");

    bool running = true;

    while(running)
    {
        clock->beginning = SDL_GetPerformanceCounter();

        if (SDL_WaitEventTimeout(&game.event, 1))
        {
            while (SDL_PollEvent(&game.event))
            {
                if (game.event.type == SDL_QUIT) running = false;
            }
        }

        idle->timer += clock->delta_time;

        if (idle->timer > idle->delay)
        {
            idle->timer -= idle->delay;
            idle->frame_index = (idle->frame_index + 1) % total_frames;
            int x = idle->frame_index * idle_w;
            sprite.change_frame(x, 0);

            SDL_SetRenderDrawColor(game.renderer, 0xf4, 0xf4, 0xf4, 0xff);
            SDL_RenderClear(game.renderer);
            sprite.render(game.renderer);
            SDL_RenderPresent(game.renderer);
        }

        clock->ending = SDL_GetPerformanceCounter();
        clock->delta_time = get_delta_time(clock->beginning, clock->ending);

        clock_delay(clock->delta_time, clock->ms_framerate_target);
        clock->delta_time = get_delta_time(clock->beginning, SDL_GetPerformanceCounter());
    }

    free(clock);
    free(idle);
    free_img_t(sheet);

    free(game.title);

    SDL_DestroyRenderer(game.renderer);
    SDL_DestroyWindow(game.window);

    IMG_Quit();
    SDL_Quit();

    return EXIT_SUCCESS;
}