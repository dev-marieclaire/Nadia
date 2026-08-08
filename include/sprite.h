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

        float scale, rotation_angle;
        int base_w, base_h;

        bool flip_h = false;

    public:

        void change_frame(uint16_t x, uint16_t y)
        {
            int max_x = atlas->w - clip.w;
            int max_y = atlas->h - clip.h;

            if (x < 0) x = 0;
            if (x > max_x) x = max_x;

            if (y < 0) y = 0;
            if (y > max_y) y = max_y;

            clip.x = x;
            clip.y = y;
        }

        void set_frame_by_index(uint16_t frame_index, uint16_t frames_per_row = 0)
        {
            if (!atlas) return;

            if (frames_per_row == 0)
                frames_per_row = atlas->w / clip.w;

                uint16_t row = frame_index / frames_per_row;
                uint16_t col = frame_index % frames_per_row;

                int x = col * clip.w;
                int y = row * clip.h;

                setClipPosition(x, y);
        }

    // Getter zone.
        int getPosition_x()
        { return destination.x; }

        int getPosition_y()
        { return destination.y; }

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
        { destination.x = x; destination.y = y; };

        void setClipDimensions(int w, int h)
        { clip.w = w; clip.h = h; }

        void setDimensions(int w, int h)
        { clip.w = destination.w = w; clip.h = destination.h = h; }

        void fScale(float factor);

        void iScale(int factor);

        void setClipPosition(int x, int y);

        bool setAtlas(img_t *img)
        {
            if (!img)
            {
                printf("Couldn't change image: new image is null");
                return false;
            }

            atlas = img;
            return (img) ? true : false;
        }

        void flip_horizontally(bool flip)
        { flip_h = flip; }

        int render(SDL_Renderer *dest)
        {
            SDL_RendererFlip flip = flip_h ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;

            int result = SDL_RenderCopyEx(
                dest, atlas->texture,
                &clip, &destination,
                rotation_angle, NULL,
                flip
            );
            if (result != 0)
                printf("RenderCopy error: %s\n", SDL_GetError());

            return result;
        }

        sprite_t();
    
        sprite_t(img_t *img, int w_px, int h_px);
};
