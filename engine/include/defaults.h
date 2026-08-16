#define _GNU_SOURCE 1





#ifdef __DJGPP__

#else

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define DEFAULT_IMG_FLAGS IMG_INIT_JPG | IMG_INIT_PNG

#endif
