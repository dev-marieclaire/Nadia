ifeq ($(TARGET),MODERN)
    SDL_CFLAGS := $(shell pkg-config --cflags sdl2 SDL2_image 2>/dev/null)
    ifeq ($(SDL_CFLAGS),)
        SDL_CFLAGS := -I/usr/include/SDL2 -D_REENTRANT
    endif
    CFLAGS   += -D__MODERN__ $(SDL_CFLAGS)
    CXXFLAGS += -D__MODERN__ $(SDL_CFLAGS)
    # For linking examples – add this so examples can link
    LDFLAGS  += $(shell pkg-config --libs sdl2 SDL2_image 2>/dev/null || echo -lSDL2 -lSDL2_image)
endif

ifeq ($(TARGET),OLD)
    ALLEGRO_CFLAGS := -I/usr/local/include/allegro
    ifeq ($(shell uname -s),Linux)
        ALLEGRO_CFLAGS := -I/usr/include/allegro
    endif
    CFLAGS   += -D__OLD__ $(ALLEGRO_CFLAGS)
    CXXFLAGS += -D__OLD__ $(ALLEGRO_CFLAGS)
    LDFLAGS  += -lallegro
endif
