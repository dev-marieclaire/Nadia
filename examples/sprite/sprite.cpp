// Sprite manipulation example.

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
// #include <time.h>

#include "init.h"

#include "screen.h"
#include "input.h"

#include "strings.h"
#include "img_t.h"
#include "sprite.h"

int main()
{
    game_t game;
    img_t *img;

    mouse_t mouse;
    keyboard_t clavier; // Clavier is keyboard in French, it looks and sounds cooler imo.

    // Prevents accidental flags by setting every value to 0.
    memset(&game, 0, sizeof(game));
    game.title = NULL;

    game.winflags = SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_INPUT_FOCUS | SDL_WINDOW_MOUSE_FOCUS;

    // Must be defined before creating a window and renderer.
    const int base_win_w = game.win_w = 320 << 1;
    const int base_win_h = game.win_h = 200 << 1;

    game.title = string("SPRITE: PROOF OF CONCEPT");

    init_everything(&game);

    game.framerate_target = 60;
    const double ms_framerate_target = 1.0f / game.framerate_target;
    
    SDL_RendererInfo info;
    SDL_GetRendererInfo(game.renderer, &info);
    printf("Renderer: %s\n", info.name);
    printf("Flags: %d\n", info.flags);

    // Stores a dithered image of The Houses of Parliment.
    img = create_img_t(game.renderer, "./dither.bmp", "Parlements de Londres");

    // Defines a sprite with the recently allocated image.
    sprite_t sprite(img, 320, 256);
    sprite.fScale(1.0f);

    sprite.setClipPosition(
        (sprite.getAtlas()->area.w >> 1) - (sprite.getClipFrame().w >> 2),
        (sprite.getAtlas()->area.h >> 1) - (sprite.getClipFrame().h)
    );

    sprite.position(
        game.center.x - (sprite.getFrame().w >> 1),
        game.center.y - (sprite.getFrame().h >> 1)
    );

    memset(&mouse, 0, sizeof(mouse));
    mouse.sensitivity = 180.0f;

    memset(&clavier, 0, sizeof(clavier));

    // Positive directions move down and right.
    // Negative directions move up and left.
    int dir[2];
    float distance = 360.0f;

    uint8_t first_frame = 0;

    float scale = 1.0f;
    float window_scale = 1.0f;

    double dt = 0.0f;

    // Calculates the velocity of horizontal and vertical movement
    auto get_horizontal = [&]() -> float
    { return dir[0] * distance * dt ; };

    auto get_vertical = [&]() -> float
    { return dir[1] * distance * dt; };

    while(true) // All game logic goes here.
    {
        // Calculate dt time
        uint64_t frame_start = SDL_GetPerformanceCounter();

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

                        if (mouse.abs_x >= sprite.getFrame().x &&
                            mouse.abs_y >= sprite.getFrame().y &&
                            mouse.abs_x <= sprite.getFrame().w + sprite.getFrame().x &&
                            mouse.abs_y <= sprite.getFrame().h + sprite.getFrame().y)
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
            int dx = sprite.getClipFrame().x + ((mouse.rel_x * mouse.sensitivity) * dt * -1);
            int dy = sprite.getClipFrame().y + ((mouse.rel_y * mouse.sensitivity) * dt * -1);

            sprite.setClipPosition(dx, dy);
        }

        // Checks if a key was pressed while avoiding interruptions in the player's movement.
        clavier.pressed = (
            clavier.state[SDL_SCANCODE_RIGHT] || clavier.state[SDL_SCANCODE_LEFT] ||
            clavier.state[SDL_SCANCODE_DOWN] || clavier.state[SDL_SCANCODE_UP] ||
            clavier.state[SDL_SCANCODE_Z] || clavier.state[SDL_SCANCODE_X] ||
            clavier.state[SDL_SCANCODE_C] || clavier.state[SDL_SCANCODE_V] ||
            clavier.state[SDL_SCANCODE_F] || clavier.state[SDL_SCANCODE_D]) ? true : false;
        
        // I realized both objects and window/UI must have separate input handlers.
        // Avoids doing rendering and heavy stuff is there are no differences between the last and current frames.
        if (clavier.pressed == true || mouse.clicking == true || first_frame == 0)
        {
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
            // when pressing LEFT and RIGHT at the same time.
            // Unnecessary for vertical movement since there is no preceivable difference.
            if (!clavier.state[SDL_SCANCODE_RIGHT] && !clavier.state[SDL_SCANCODE_LEFT]) dir[0] = 0;

            if (clavier.state[SDL_SCANCODE_RIGHT] && !clavier.state[SDL_SCANCODE_LEFT]) dir[0] = 1;
            else if (!clavier.state[SDL_SCANCODE_RIGHT] && clavier.state[SDL_SCANCODE_LEFT]) dir[0] = -1;

            if (clavier.state[SDL_SCANCODE_RIGHT] && !clavier.state[SDL_SCANCODE_LEFT] && dir[0] == -1) dir[0] = 1;
            if (!clavier.state[SDL_SCANCODE_RIGHT] && clavier.state[SDL_SCANCODE_LEFT] && dir[0] == 1) dir[0] = -1;

            if (clavier.state[SDL_SCANCODE_Z] || clavier.state[SDL_SCANCODE_X])
                scale += (clavier.state[SDL_SCANCODE_Z] ? 1.0f * dt : (clavier.state[SDL_SCANCODE_X] ? -1.0f * dt : 0));

            if (clavier.state[SDL_SCANCODE_C] || clavier.state[SDL_SCANCODE_D]) window_scale += 0.01f;
            if (clavier.state[SDL_SCANCODE_V] || clavier.state[SDL_SCANCODE_V]) window_scale -= 0.01f;

            if (dir[0] != 0 || dir[1] != 0)
            {
                sprite.position(
                    sprite.getPosition_x() + get_horizontal(),
                    sprite.getPosition_y() + get_vertical()
                );
            }

            if (clavier.state[SDL_SCANCODE_Z] || clavier.state[SDL_SCANCODE_X]) sprite.fScale(scale);

            if (clavier.state[SDL_SCANCODE_C] || clavier.state[SDL_SCANCODE_V])
            {
                SDL_GetWindowSize(game.window, (int *) &game.win_w, (int *) &game.win_h);
                SDL_SetWindowSize(game.window, (int) (base_win_w * window_scale), (int) (base_win_h * window_scale));
            }

            if (clavier.state[SDL_SCANCODE_D] || clavier.state[SDL_SCANCODE_F])
            {
                SDL_GetWindowSize(game.window, (int *) &game.win_w, (int *) &game.win_h);
                SDL_RenderSetScale(game.renderer, window_scale, window_scale);
                SDL_SetWindowSize(game.window, (int) (base_win_w * window_scale), (int) (base_win_h * window_scale));
            }

            sprite.render(game.renderer);

            SDL_RenderPresent(game.renderer);

            // Renders in the first frame, avoiding a black screen in the beginning.
            if (first_frame == 0) first_frame++;
        }

        uint64_t frame_end = SDL_GetPerformanceCounter();

        dt = (double) (frame_end - frame_start) / (double) SDL_GetPerformanceFrequency();

        if (dt < ms_framerate_target) // Prevents spiral of death
            SDL_Delay((ms_framerate_target - dt) * 1000.0f); // Tiny sleep prevents CPU from spinning
            dt = ms_framerate_target;        
    }

    free_img_t(img);

    free(game.title);

    SDL_DestroyRenderer(game.renderer);
    SDL_DestroyWindow(game.window);

    IMG_Quit();
    SDL_Quit();

    return EXIT_SUCCESS;
}
