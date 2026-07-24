#include "sprite.h"

void sprite_t::render(SDL_Renderer *dest)
{
    SDL_RenderCopy(dest, atlas->getTexture(), &clip, &quad);
}
