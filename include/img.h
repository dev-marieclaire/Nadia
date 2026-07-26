#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class img_t
{
    private:
        SDL_Surface *data;
        SDL_Texture *texture;

        bool load(const char *src);

        // Frees the memory assigned to the image.
        void clean();

    public:
        // Getter zone
        SDL_Rect getArea();

        SDL_Surface *getData()
        { return data; }

        SDL_Texture *getTexture()
        { return texture; }

        bool setOpacity(float alpha)
        {
            if (SDL_SetTextureAlphaMod(texture, alpha)
                && alpha <= 255 && alpha >= 0)
                return true;
            
            printf("Error in applying opacity: ", SDL_GetError());
            return false;
        }

        // Setter zone
        void setData(SDL_Surface *src)
        { data = src; }

        // Autres choses
        void createTextureFromSurface(SDL_Renderer *renderer)
        { texture = SDL_CreateTextureFromSurface(renderer, data); }

        void reload(const char *src)
        { clean(); load(src); }

        img_t(const char *src)
        { load(src); }

        ~img_t()
        { clean(); }
};
