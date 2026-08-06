#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "img_t.h"

class sprite_t
{
    private:
        SDL_Rect destination; // This is used for render manipulation. Scaling depends in this property.
        SDL_Rect clip;  // Defines what the sprite is currently showing.
        img_t *atlas;   // The sprite's image.

        int x, y;
        int w, h;

        float scale;
        int base_w, base_h;

    public:

        void change_frame(uint16_t x, uint16_t y)
        {
            int max_x = atlas->area.w - clip.w;
            int max_y = atlas->area.h - clip.h;

            if (x < 0) x = 0;
            if (x > max_x) x = max_x;

            if (y < 0) y = 0;
            if (y > max_y) y = max_y;

            clip.x = x;
            clip.y = y;
        }

    // Getter zone.
        SDL_Rect getPosition()
        { return {x, y}; }

        int getPosition_x()
        { return x; }

        int getPosition_y()
        { return y; }

        SDL_Rect getFrame()
        { return destination; }
        
        SDL_Rect getClipFrame()
        { return clip; }

        img_t *getAtlas()
        { return atlas; }

        float getScale()
        { return scale; }

    // Setter zone.
        void position(int x, int y)
        { destination.x = this->x = x; destination.y = this->y = y; };

        void setClipDimensions(int w, int h)
        { clip.w = w; clip.h = h; }

        void fScale(float factor);

        void iScale(int factor);

        void setClipPosition(int x, int y);

        int render(SDL_Renderer *dest)
        {
            int result = SDL_RenderCopy(dest, atlas->texture, &clip, &destination);
            if (result != 0)
                printf("RenderCopy error: %s\n", SDL_GetError());

            return result;
        }

        sprite_t();
    
        sprite_t(img_t *img, int w_px, int h_px);
};
