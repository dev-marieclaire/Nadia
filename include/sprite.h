#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "img.h"

class sprite_t
{
    private:
        SDL_Rect clip;
        SDL_Rect quad;
        img_t *atlas;

    public:
        void position(int x, int y)
        { quad.x = x; quad.y = y; };

        // This is more likely for a kinematic body.
        // Will remain here until added.
        void move_x(int x)
        { quad.x += x; };

        void move_y(int y)
        { quad.y += y; };

        void fScale(float factor)
        {
            if (factor > 0)
            {
                quad.w = (int) quad.w * factor;
                quad.h = (int) quad.h * factor;
            }
            else
            {
                printf("Warning: scale factor must be major than 0.");
            }
        }

        void iScale(int factor)
        {
            if (factor > 0)
            {
                quad.w *= factor;
                quad.h *= factor;
            }
            else
            {
                printf("Warning: scale factor must be major than 0.");
            }
        }

        void clipPosition(int x, int y)
        { clip.x = x; clip.y = y; }

        void clipDimensions(int w, int h)
        { clip.w = w; clip.h = h; }

        img_t *getAtlas()
        { return atlas; }

        SDL_Rect getArea()
        { return quad; }

        SDL_Rect getClipArea()
        { return clip; }
    
        sprite_t(img_t *img, int w_px, int h_px)
        {
            atlas = img;
            clipDimensions(w_px, h_px);
            clipPosition(0, 0);

            quad = {0, 0, clip.w, clip.h};
        }

        sprite_t(img_t *img, int w_px, int h_px, int x_px, int y_px)
        {
            atlas = img;
            clipDimensions(w_px, h_px);
            clipPosition(x_px, y_px);

            quad = {0, 0, clip.w, clip.h};
        }

        // sprite_t(img_t *img, int w_px, int h_px, uint16_t x_tile, uint16_t y_tile)
        // {
        //     atlas = img;
        //     setDimensions(w_px, h_px);
        //     setClipPosition(x_tile * w_px, y_tile * h_px);
        // }

        void render(SDL_Renderer *rend);
};
