#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "img_t.h"

class sprite_t
{
    private:
        SDL_Rect frame;
        SDL_Rect clip;
        img_t *atlas;

        int x, y;
        int w, h;

        float scale;
        int base_w, base_h;

    public:
    // Getter zone.
        SDL_Rect getPosition()
        { return {x, y}; }

        int getPosition_x()
        { return x; }

        int getPosition_y()
        { return y; }

        SDL_Rect getFrame()
        { return frame; }
        
        SDL_Rect getClipFrame()
        { return clip; }

        img_t *getAtlas()
        { return atlas; }

        float getScale()
        { return scale; }

    // Setter zone.
        void position(int x, int y)
        { frame.x = this->x = x; frame.y = this->y = y; };

        void setClipDimensions(int w, int h)
        { clip.w = w; clip.h = h; }

        void fScale(float factor);

        void iScale(int factor);

        void setClipPosition(int x, int y);

        void render(SDL_Renderer *dest)
        { SDL_RenderCopy(dest, atlas->texture, &clip, &frame); }

        sprite_t();
    
        sprite_t(img_t *img, int w_px, int h_px);
};
