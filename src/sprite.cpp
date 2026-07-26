#include "sprite.h"

sprite_t::sprite_t(img_t *img, int w_px, int h_px)
{
    atlas = img;
    setClipDimensions(w_px, h_px);
    setClipPosition(0, 0);

    x = y = 0;

    scale = 1.0f;
    frame = {0, 0, clip.w, clip.h};
}

void sprite_t::fScale(float factor)
{
    if (factor <= 0.00f) factor = 0.01f;
    if (factor >= 10.0f) factor = 10.0f;

    if ((scale - factor) != 0)
    {
        scale = factor;
        frame.w = (int) (clip.w * factor);
        frame.h = (int) (clip.h * factor);
    }
}

void sprite_t::iScale(int factor)
{
    if (factor <= 0.00f) factor = 0.01f;
    if (factor >= 10.0f) factor = 10.0f;

    if ((scale - factor) != 0)
    {
        scale = (float) factor;
        frame.w = (int) (clip.w * factor);
        frame.h = (int) (clip.h * factor);
    }
}

void sprite_t::setClipPosition(int x, int y)
{
    if (x >= atlas->getArea().w - clip.w)
        x = atlas->getArea().w - clip.w;
    if (y >= atlas->getArea().h - clip.h)
        y = atlas->getArea().h - clip.h;

    if (x <= 0) x = 0;
    if (y <= 0) y = 0;

    clip.x = x;
    clip.y = y;
}
