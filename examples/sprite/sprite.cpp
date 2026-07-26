// Sprite manipulation example.

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <time.h>

#include "init.h"

#include "screen.h"
#include "input.h"

#include "img.h"
#include "sprite.h"

int main()
{
    game_t game;
    memset(&game, 0, sizeof(game)); // Prevents accidental flags by setting every value to 0.

    const char *title = "SPRITE: PROOF OF CONCEPT";
    size_t len = strlen(title);

    game.title = (char*) malloc(len + 1);
    if (game.title == NULL)
    {
        fprintf(stderr, "malloc failed!\n");
        return 1;
    }

    strcpy(game.title, title);
    printf("Title copied: '%s'\n", game.title);

    game.win_w = 320 << 1;
    game.win_h = 240 << 1;

    init_everything(&game);

    // Stores a dithered image of The Houses of Parliment.
    img_t house("./dither.bmp");
    house.createTextureFromSurface(game.renderer);

    sprite_t sprite(&house, 320, 256);
    sprite.fScale(1.0f);

    sprite.setClipPosition(
        (sprite.getAtlas()->getData()->w >> 1) - (sprite.getClipFrame().w >> 2),
        (sprite.getAtlas()->getData()->h >> 1) - (sprite.getClipFrame().h)
    );

    sprite.position(
        game.center.x - (sprite.getFrame().w >> 1),
        game.center.y - (sprite.getFrame().h >> 1)
    );

    SDL_RendererInfo info;
    SDL_GetRendererInfo(game.renderer, &info);
    printf("Renderer: %s\n", info.name);
    printf("Flags: %d\n", info.flags);

    mouse_t mouse; memset(&mouse, 0, sizeof(mouse));
    mouse.sensitivity = 4.0f;

    keyboard_t clavier; // Clavier is keyboard in French, it looks and sounds cooler imo.
    memset(&clavier, 0, sizeof(clavier));

    // Delta time variables
    Uint64 current = SDL_GetPerformanceCounter();
    Uint64 previous = 0;
    float delta = 0.0f;
    const Uint64 freq = SDL_GetPerformanceFrequency();

    // Positive directions move down and right.
    // Negative directions move up and left.
    int dir[2];
    float distance = 360.0f;

    // Calculates the velocity of horizontal and vertical movement
    auto get_horizontal = [&]() -> float
    { return dir[0] * distance * delta ; };

    auto get_vertical = [&]() -> float
    { return dir[1] * distance * delta; };

    uint8_t first_frame = 0;

    float scale = 1.0f;

    while(true) // All game logic goes here.
    {
        /* FPS counter. May decomment later.
        static Uint32 lastTime = 0;
        static int frames = 0;
        frames++;

        if (SDL_GetTicks() - lastTime > 1000) {
            printf("FPS: %d\n", frames);
            frames = 0;
            lastTime = SDL_GetTicks();
        }
        */

        // Calculate delta time
        current = SDL_GetPerformanceCounter();
        // Delta time is the temporal difference between the current and the previous frame.
        delta = (float)(current - previous) / (float)freq;
        if (delta > 0.05f) delta = 0.05f; // Prevents spiral of death
        previous = current;

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
            int dx = sprite.getClipFrame().x + ((mouse.rel_x * mouse.sensitivity) * -1);
            int dy = sprite.getClipFrame().y + ((mouse.rel_y * mouse.sensitivity) * -1);

            sprite.setClipPosition(dx, dy);
        }

        // Checks if a key was pressed while avoiding interruptions in the player's movement.
        clavier.pressed = (
            clavier.state[SDL_SCANCODE_RIGHT] || clavier.state[SDL_SCANCODE_LEFT] ||
            clavier.state[SDL_SCANCODE_DOWN] || clavier.state[SDL_SCANCODE_UP] ||
            clavier.state[SDL_SCANCODE_Z] || clavier.state[SDL_SCANCODE_X]) ? true : false;
        
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

            // Left it just in case.
            // if (!clavier.state[SDL_SCANCODE_DOWN] && !clavier.state[SDL_SCANCODE_UP]) dir[1] = 0;

            // if (clavier.state[SDL_SCANCODE_DOWN] && !clavier.state[SDL_SCANCODE_UP]) dir[1] = 1;
            // else if (!clavier.state[SDL_SCANCODE_DOWN] && clavier.state[SDL_SCANCODE_UP]) dir[1] = -1;

            // if (clavier.state[SDL_SCANCODE_DOWN] && !clavier.state[SDL_SCANCODE_UP] && dir[1] == -1) dir[1] = 1;
            // if (!clavier.state[SDL_SCANCODE_DOWN] && clavier.state[SDL_SCANCODE_UP] && dir[1] == 1) dir[1] = -1;

            scale += (clavier.state[SDL_SCANCODE_Z] ? 1.0f * delta : (clavier.state[SDL_SCANCODE_X] ? -1.0f * delta : 0));

            sprite.position(
                sprite.getPosition_x() + get_horizontal(),
                sprite.getPosition_y() + get_vertical()
            );

            sprite.fScale(scale);

            sprite.render(game.renderer);

            SDL_RenderPresent(game.renderer);

            // Renders in the first frame, avoiding a black screen in the beginning.
            if (first_frame == 0) first_frame++;
        }

        // Add this even with VSync
        SDL_Delay(1); // Tiny sleep prevents CPU from spinning
    }

    free(game.title);

    SDL_DestroyWindow(game.window);
    IMG_Quit();
    SDL_Quit();

    return 0;
}
