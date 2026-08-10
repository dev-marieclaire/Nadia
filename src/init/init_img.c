// init_image.c

#include <SDL2/SDL_image.h>

void init_img(int flags)
{   int img_initted = IMG_Init(flags);

    if(img_initted & flags != flags) // handle error
    {   printf("IMG_Init: Failed to init required jpg and png support!\n");
        printf("IMG_Init: %s\n", IMG_GetError());
    }
}
