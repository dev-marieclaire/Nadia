// Sprite manipulation example.

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

#define TITLE       (char *) "ANIMATED SPRITES"
#define BASE_WIN_W  (int) (320 << 1)
#define BASE_WIN_H  (int) (200 << 1)
#define WINFLAGS    SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_INPUT_FOCUS | SDL_WINDOW_MOUSE_FOCUS

game_t game;
screen_t screen = {
    BASE_WIN_W, BASE_WIN_H,
    SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED
};

delta_t *delta = create_delta_t(60);

mouse_t mouse;
keyboard_t clavier; // Clavier is keyboard in French, it looks and sounds cooler imo.

int main()
{
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest");
    init_everything(&game, TITLE, &screen, WINFLAGS, -1, DEFAULT_REND_FLAGS);

    SDL_RendererInfo info;
    SDL_GetRendererInfo(game.renderer, &info);
    printf("Renderer: %s\n", info.name);
    printf("Flags: %d\n", info.flags);

    // Stores a dithered image of The Houses of Parliment.
    img_t *img = create_img_t(game.renderer, "./dither.bmp", "Parlements de Londres");

    // Defines a sprite with the recently allocated image.
    sprite_t sprite(img, img->w >> 2, img->h >> 2);

    sprite.frame_position(
        img->w - sprite.get_width(),
        sprite.get_height() - (sprite.get_height() >> 3)
    );

    sprite.position(
        (screen.w / 2) - (sprite.get_width() >> 1),
        (screen.h / 2) - (sprite.get_height() >> 1)
    );

    mouse.sensitivity = 0.24f;

    // Positive directions move down and right.
    // Negative directions move up and left.
    int     dir[2] = {0, 0};
    float   distance = 0.48f;

    uint8_t first_frame = 0;

    float   scale = 1.0f;
    float   window_scale = 1.0f;
    delta_t *delta = create_delta_t(60);

    while(true) // All game logic goes here.
    {
        uint32_t current_time = SDL_GetTicks();
        delta->time_ms = current_time - delta->previous_time_ms;
        delta->previous_time_ms = current_time;

        if (delta->time_ms > 100) delta->time_ms = 16;
        if (delta->time_ms == 0) delta->time_ms = 1;

        clavier.state = (uint8_t*) SDL_GetKeyboardState(NULL);

        // Returns a flag indicating which mouse buttons are being pressed
        mouse.buttonflags = SDL_GetMouseState(&mouse.abs_x, &mouse.abs_y);
        // GetRelative gets the difference in distance between the position saved in the last call and the new call.
        SDL_GetRelativeMouseState(&mouse.rel_x, &mouse.rel_y);

        while(SDL_PollEvent(&game.event))
        {
            if (game.event.type == SDL_QUIT) exit(0);

            switch (game.event.type)
            {
                case SDL_MOUSEBUTTONDOWN:
                    if (game.event.button.button == SDL_BUTTON_LEFT && mouse.clicking == false)
                    {
                        mouse.click_pos.x = mouse.abs_x;
                        mouse.click_pos.y = mouse.abs_y;

                        if (mouse.abs_x >= sprite.get_position().x &&
                            mouse.abs_y >= sprite.get_position().y &&
                            mouse.abs_x <= sprite.get_frame_width() + sprite.get_position().x &&
                            mouse.abs_y <= sprite.get_frame_height() + sprite.get_position().y)
                            mouse.clicking = true;
                    }
                    break;

                case SDL_MOUSEBUTTONUP:
                    if (game.event.button.button == SDL_BUTTON_LEFT && mouse.clicking == true)
                        mouse.clicking = false;
                break;

                case SDL_MOUSEMOTION:
                    if (mouse.clicking && !mouse.moving &&
                        mouse.rel_x != 0 && mouse.rel_y != 0)
                        mouse.moving = true;
                    else
                        mouse.moving = false;
            }
        }

        if ((mouse.buttonflags & SDL_BUTTON_LEFT) == true && mouse.moving == true)
        {
            uint32_t dx = sprite.get_frame_position().x + ((mouse.rel_x * mouse.sensitivity) * (delta->time_ms) * -1);
            uint32_t dy = sprite.get_frame_position().y + ((mouse.rel_y * mouse.sensitivity) * (delta->time_ms) * -1);

            sprite.set_frame(dx, dy);
        }

        // Checks if a key was pressed while avoiding interruptions in the player's movement.
        clavier.pressed = (
            clavier.state[SDL_SCANCODE_RIGHT] || clavier.state[SDL_SCANCODE_LEFT] ||
            clavier.state[SDL_SCANCODE_DOWN] || clavier.state[SDL_SCANCODE_UP] ||
            clavier.state[SDL_SCANCODE_Z] || clavier.state[SDL_SCANCODE_X] ||
            clavier.state[SDL_SCANCODE_C] || clavier.state[SDL_SCANCODE_V] ||
            clavier.state[SDL_SCANCODE_F] || clavier.state[SDL_SCANCODE_D]) ? true : false;
        
        if (clavier.state[SDL_SCANCODE_A]) window_scale += 0.5f * delta->time_ms;
        if (clavier.state[SDL_SCANCODE_S]) window_scale -= 0.5f * delta->time_ms;

        if (window_scale < 0.2f) window_scale = 0.2f;
        if (window_scale > 3.0f) window_scale = 3.0f;
        
        // I realized both objects and window/UI must have separate input handlers.
        // Avoids doing rendering and heavy stuff is there are no differences between the last and current frames.
        if (clavier.pressed == true || mouse.clicking == true || first_frame == 0)
        {
            // printf("press!");
            // #fcd7d7
            SDL_SetRenderDrawColor(game.renderer, 0xfc, 0xd7, 0xd7, 0xff);
            SDL_RenderClear(game.renderer);

            // Since true = 1 and false = 0 then
            // true  - false = 1
            // false - true  = -1
            // true  - true  = 0 <-- KEY CANCELING OCCURS. SEE CODE BELOW.
            dir [1] = clavier.state[SDL_SCANCODE_DOWN] - clavier.state[SDL_SCANCODE_UP];

            // Responsive horizontal movement.
            // This was implemented so whenever avoids key cancelling
            // when pressing LEFT and RIGHT at the same time_ms.
            // Unnecessary for vertical movement since there is no preceivable difference.
            dir[0] = 0;
            if (clavier.state[SDL_SCANCODE_RIGHT] && !clavier.state[SDL_SCANCODE_LEFT]) dir[0] = 1;
            if (!clavier.state[SDL_SCANCODE_RIGHT] && clavier.state[SDL_SCANCODE_LEFT]) dir[0] = -1;

            if (clavier.state[SDL_SCANCODE_Z] || clavier.state[SDL_SCANCODE_X])
            {
                scale += (clavier.state[SDL_SCANCODE_Z]
                    ? 0.001f * (delta->time_ms)
                    : (clavier.state[SDL_SCANCODE_X] ? -0.001f * (delta->time_ms) : 0));
            }

            // printf("Vel x: %f\n", (dir[0] * distance * delta->time_ms));
            // printf("Delta time: %d, Distance: %f\n", delta->time_ms, distance);

            if (dir[0] != 0 || dir[1] != 0)
            {
                sprite.position(
                    sprite.get_position().x + (dir[0] * distance * delta->time_ms),
                    sprite.get_position().y + (dir[1] * distance * delta->time_ms)
                );
            }

            if (clavier.state[SDL_SCANCODE_Z] || clavier.state[SDL_SCANCODE_X]) sprite.fScale(scale);

            if (clavier.state[SDL_SCANCODE_A] || clavier.state[SDL_SCANCODE_S])
            {
                int win_w = BASE_WIN_W * window_scale;
                int win_h = BASE_WIN_H * window_scale;
                SDL_SetWindowSize(game.window, win_w, win_h);
                SDL_RenderSetLogicalSize(game.renderer, BASE_WIN_W, BASE_WIN_H);
            }

            sprite.render(game.renderer);

            SDL_RenderPresent(game.renderer);

            // Renders in the first frame, avoiding a black screen in the beginning.
            if (first_frame == 0) first_frame++;
        }

        uint32_t elapsed = SDL_GetTicks() - current_time;
        dt_delay(elapsed, delta->ms_framerate_target);
    }

    free_img_t(img);

    free(game.title);

    SDL_DestroyRenderer(game.renderer);
    SDL_DestroyWindow(game.window);

    IMG_Quit();
    SDL_Quit();

    return EXIT_SUCCESS;
}
