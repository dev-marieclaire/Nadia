#pragma once

// #ifdef __DJGPP__

// #else

// #include <SDL2/SDL.h>
// #include <SDL2/SDL_image.h>

// #include "img_t.h"

// class sprite_t
// {
//     private:
//         SDL_Rect    render_area;    // Stores the area that the renderer is going to use to render the sprite.
//         SDL_Rect    frame;  // Defines what the sprite is currently showing, the logical sprite area.
//         img_t       *atlas; // The sprite's image.

//         // Self-explanatory, I think.
//         float       scale;
//         float       rotation_angle;

//         int         base_w, base_h; // Base width and height, we'll apply scale over these variables.
//         bool        flip_h;

//     public:
//     // Getter zone.
//         SDL_Point get_position()
//         { return {render_area.x, render_area.y}; }

//         int get_width()
//         { return render_area.w; }

//         int get_height()
//         { return render_area.h; }

//         SDL_Point get_frame_position()
//         { return {frame.x, frame.y}; }

//         int get_frame_width()
//         { return frame.w; }

//         int get_frame_height()
//         { return frame.h; }

//         // img_t *get_atlas()
//         // { return atlas; }

//         float get_scale()
//         { return scale; }

//     // Setter zone.
//         void position(int x, int y)
//         { render_area.x = x; render_area.y = y; };

//         void frame_position(int x, int y)
//         { frame.x = x; frame.y = y; }

//         void frame_dimensions(int w, int h)
//         { frame.w = w; frame.h = h; }

//         void dimensions(int w, int h)
//         { render_area.w = (frame.w = w) * scale; render_area.h = (frame.h = h) * scale; }

//         void flip_horizontally(bool flip)
//         { flip_h = flip; }

//         void fScale(float factor);

//         void iScale(int factor);

//         void set_frame(int x, int y);

//         void set_frame_by_index(uint16_t frame_index, uint16_t frames_per_row = 0);

//         bool set_image(img_t *img);

//         int render(SDL_Renderer *dest);

//         sprite_t();
    
//         sprite_t(img_t *img, uint32_t w_px, uint32_t h_px);
// };

// #endif
