ENGINE_ROOT := $(dir $(lastword $(MAKEFILE_LIST)))

ifeq ($(TARGET), OLD)
    DJGPP_GCC := $(shell which i586-pc-msdosdjgpp-g++ 2>/dev/null)

    ifeq ($(DJGPP_GCC),)
        DJGPP_GCC := /usr/local/djgpp/bin/i586-pc-msdosdjgpp-g++
    endif

    ifeq ($(wildcard $(DJGPP_GCC)),)
        $(error "DJGPP compiler not found.")
    endif

    CC      = $(DJGPP_GCC)
    CFLAGS  = -I$(ENGINE_ROOT)include -D__OLD__ -DALLEGRO_NO_MAGIC_MAIN
    LDFLAGS = -L$(ENGINE_ROOT)../lib/allegro/djgpp -lalleg
    PLATFORM_SRC := $(wildcard $(ENGINE_ROOT)src/platform/old/*.c)
    LIB_NAME = libengine_old.a
else
    CC      = g++
    CFLAGS  = -I$(ENGINE_ROOT)include -D__MODERN__ `sdl2-config --cflags`
    LDFLAGS = `sdl2-config --libs` -lSDL2_image -lSDL2_ttf -lm
    PLATFORM_SRC := $(wildcard $(ENGINE_ROOT)src/platform/modern/*.c)
    LIB_NAME = libengine_modern.a
endif

CORE_SRC := $(wildcard $(ENGINE_ROOT)src/core/*.c)
GRAPHICS_SRC := $(wildcard $(ENGINE_ROOT)src/graphics/*.c) $(wildcard $(ENGINE_ROOT)src/graphics/*.cpp)
ALL_SRC  := $(CORE_SRC) $(GRAPHICS_SRC) $(PLATFORM_SRC)

OBJDIR   := $(ENGINE_ROOT)build/$(shell echo $(TARGET) | tr '[:upper:]' '[:lower:]')
OBJS     := $(patsubst $(ENGINE_ROOT)src/%.c,$(OBJDIR)/%.o,$(ALL_SRC))
LIB      := $(ENGINE_ROOT)lib/$(LIB_NAME)

.PHONY: all clean

all: $(LIB)

$(LIB): $(OBJS)
	@mkdir -p $(dir $@)
	ar rcs $@ $^

$(OBJDIR)/%.o: $(ENGINE_ROOT)src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR) $(ENGINE_ROOT)lib/*.a