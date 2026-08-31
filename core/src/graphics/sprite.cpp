#include <graphics/graphics.h>

// sprite_t::sprite_t(img_t *img, uint32_t w_px, uint32_t h_px)
// {
//     atlas = img;
//     if (!atlas) printf("Error: Sprite atlas is NULL.\n");

//     if (w_px > atlas->w)
//     {
//         w_px = atlas->w;
//         printf("Warning: set width is greater than atla's width.\n");
//     }

//     if (h_px > atlas->h)
//     {
//         h_px = atlas->h;
//         printf("Warning: set height is greater than atla's height.\n");
//     }

//     frame.x = frame.y = 0;
//     frame.w = w_px; frame.h = h_px;

//     scale = 1.0f;
//     flip_h = false;

//     render_area = {0, 0, (int) w_px, (int) h_px};
// }

// // SPRITE MODIFIERS.
// void sprite_t::fScale(float factor)
// {
//     if (factor <= 0.00f) factor = 0.01f;
//     if (factor >= 10.0f) factor = 10.0f;

//     if ((scale - factor) != 0)
//     {
//         scale = factor;
//         render_area.w = (int) (frame.w * factor);
//         render_area.h = (int) (frame.h * factor);
//     }
// }

// void sprite_t::iScale(int factor)
// {
//     if (factor <= 0.00f) factor = 0.01f;
//     if (factor >= 10.0f) factor = 10.0f;

//     if ((scale - factor) != 0)
//     {
//         scale = (float) factor;
//         render_area.w = (int) (frame.w * factor);
//         render_area.h = (int) (frame.h * factor);
//     }
// }

// void sprite_t::set_frame(int x, int y)
// {
//     if (x > atlas->w - frame.w) x = atlas->w - frame.w;
//     if (y > atlas->h - frame.h) y = atlas->h - frame.h;

//     if (x < 0) x = 0;
//     if (y < 0) y = 0;

//     frame.x = x;
//     frame.y = y;
// }

// void sprite_t::set_frame_by_index(uint16_t frame_index, uint16_t frames_per_row)
// {
//     if (!atlas) return;

//     if (frames_per_row == 0) frames_per_row = atlas->w / frame.w;

//     uint16_t row = frame_index / frames_per_row;
//     uint16_t col = frame_index % frames_per_row;

//     int x = col * frame.w;
//     int y = row * frame.h;

//     frame_position(x, y);
// }

// bool sprite_t::set_image(img_t *img)
// {
//     if (!img)
//     {
//         printf("Couldn't change image: new image is NULL.");
//         return false;
//     }

//     atlas = img; return true;
// }

// int sprite_t::render(SDL_Renderer *dest)
// {
//     SDL_RendererFlip flip = flip_h ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;

//     int result = SDL_RenderCopyEx(
//         dest, atlas->data,
//         &frame, &render_area,
//         rotation_angle, NULL,
//         flip
//     );

//     if (result != 0) printf("RenderCopy error: %s\n", SDL_GetError());

//     return result;
// }
