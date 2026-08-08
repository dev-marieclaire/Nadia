#include "sprite.h"

sprite_t::sprite_t(img_t *img, int w_px, int h_px)
{
    atlas = img;
    if (!atlas) printf("Sprite atlas is NULL.\n");

    if (w_px > atlas->w) w_px = atlas->w;
    if (h_px > atlas->h) h_px = atlas->h;
    
    clip.x = clip.y = 0;
    clip.w = w_px; clip.h = h_px;

    destination = {0, 0, w_px, h_px};
}

void sprite_t::fScale(float factor)
{
    if (factor <= 0.00f) factor = 0.01f;
    if (factor >= 10.0f) factor = 10.0f;

    if ((scale - factor) != 0)
    {
        scale = factor;
        destination.w = (int) (clip.w * factor);
        destination.h = (int) (clip.h * factor);
    }
}

void sprite_t::iScale(int factor)
{
    if (factor <= 0.00f) factor = 0.01f;
    if (factor >= 10.0f) factor = 10.0f;

    if ((scale - factor) != 0)
    {
        scale = (float) factor;
        destination.w = (int) (clip.w * factor);
        destination.h = (int) (clip.h * factor);
    }
}

void sprite_t::setClipPosition(int x, int y)
{
    if (x < 0) x = 0;
    if (x > atlas->w - clip.w)
        x = atlas->w - clip.w;

    if (y < 0) y = 0;
    if (y > atlas->h - clip.h)
        y = atlas->h - clip.h;

    clip.x = x;
    clip.y = y;
}
