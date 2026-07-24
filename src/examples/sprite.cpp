// main.c

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <time.h>

#include "defs.h"

#include "init.h"

#include "screen.h"
#include "input.h"

// #include "img.h"
// #include "sprite.h"

game_t game;

void finish()
{
    SDL_DestroyWindow(game.window);
    IMG_Quit();
    SDL_Quit();
}

int main()
{
    init_everything(&game);

    // Displays a dithered image of The Houses of Parliment
    img_t house("./dither.bmp");
    house.createTextureFromSurface(game.renderer);

    sprite_t sprite(&house, 320, 256);
    sprite.fScale(0.5);

    sprite.clipPosition(
        (sprite.getAtlas()->getData()->w >> 1) - (sprite.getClipArea().w >> 2),
        (sprite.getAtlas()->getData()->h >> 1) - (sprite.getClipArea().h)
    );

    sprite.position(
        (game.rect.w >> 1) - (sprite.getArea().w >> 1),
        (game.rect.h >> 1) - (sprite.getArea().h >> 1)
    );

    SDL_RendererInfo info;
    SDL_GetRendererInfo(game.renderer, &info);
    printf("Renderer: %s\n", info.name);
    printf("Flags: %d\n", info.flags);

    static bool rerender = true;

    while(true) // All game logic goes here.
    {
        /* FPS counter
        static Uint32 lastTime = 0;
        static int frames = 0;
        frames++;

        if (SDL_GetTicks() - lastTime > 1000) {
            printf("FPS: %d\n", frames);
            frames = 0;
            lastTime = SDL_GetTicks();
        }
        */

        const Uint8 *keys;

        // Delta time variables
        Uint64 current = SDL_GetPerformanceCounter();
        Uint64 previous = 0;
        float delta = 0.0f;
        const Uint64 freq = SDL_GetPerformanceFrequency();

        // Positive directions move down and right.
        // Negative directions move up and left.
        int dir[2];

        // Calculates the velocity of the movement
        float distance = 240.0f;

        auto get_horizontal = [&]() -> float
        { return dir[0] * distance * delta ; };

        auto get_vertical = [&]() -> float
        { return dir[1] * distance * delta; };
        
        // I realized both objects and window/UI must have separate input handlers.
        if (true)
        {
            while(SDL_PollEvent(&game.event))
            {
                if (game.event.type == SDL_QUIT) exit(0);
            }

            // Calculate delta time
            // Delta time is the temporal difference between the current and the previous frame.
            current = SDL_GetPerformanceCounter();
            delta = (float)(current - previous) / (float)freq;
            if (delta > 0.05f) delta = 0.05f; // Prevents spiral of death
            previous = current;

            keys = SDL_GetKeyboardState(NULL);

            // Since true = 1 and false = 0 then
            // true  - false = 1
            // false - true  = -1
            // true  - true  = 0 <-- KEY CANCELING OCCURS. SEE CODE BELOW.
            dir [1] = keys[SDL_SCANCODE_DOWN] - keys[SDL_SCANCODE_UP];

            // Responsive horizontal movement.
            // This was implemented so whenever avoids key cancelling
            // when pressing LEFT and RIGHT at the same time.
            // Unnecessary for vertical movement since there is no preceivable difference.
            if (!keys[SDL_SCANCODE_RIGHT] && !keys[SDL_SCANCODE_LEFT]) dir[0] = 0;

            if (keys[SDL_SCANCODE_RIGHT] && !keys[SDL_SCANCODE_LEFT]) dir[0] = 1;
            else if (!keys[SDL_SCANCODE_RIGHT] && keys[SDL_SCANCODE_LEFT]) dir[0] = -1;

            // if the pressed key doesn't match the direction, then change the direction.
            if (keys[SDL_SCANCODE_RIGHT] && !keys[SDL_SCANCODE_LEFT] && dir[0] == -1) dir[0] = 1;
            if (!keys[SDL_SCANCODE_RIGHT] && keys[SDL_SCANCODE_LEFT] && dir[0] == 1) dir[0] = -1;

            sprite.move_x(get_horizontal());
            sprite.move_y(get_vertical());

            printf("Coordinates: { %d , %d }\n", sprite.getArea().x, sprite.getArea().y);

            // #fcd7d7
            SDL_SetRenderDrawColor(game.renderer, 0xfc, 0xd7, 0xd7, 0xff);
            SDL_RenderClear(game.renderer);

            sprite.render(game.renderer);
            
            SDL_RenderPresent(game.renderer);
        }

        // Add this even with VSync
        SDL_Delay(1); // Tiny sleep prevents CPU from spinning
    }

    finish();

    return 0;
}
