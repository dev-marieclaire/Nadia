
#ifdef __DJGPP__

#else

#include <SDL2/SDL.h>

extern SDL_Window *init_window(void);
extern SDL_Window *create_custom_window(const char *title, uint x, uint y, uint w, uint h, int flags);

#endif
