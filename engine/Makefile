NADIA_ROOT := $(dir $(lastword $(MAKEFILE_LIST)))

LIB_NAME = libnadia_platform_$(shell echo $(TARGET) | tr '[:upper:]' '[:lower:]').a

ifeq ($(TARGET), OLD)
    DJGPP_GCC := $(shell which i586-pc-msdosdjgpp-g++ 2>/dev/null)

    ifeq ($(DJGPP_GCC),)
        DJGPP_GCC := /usr/local/djgpp/bin/i586-pc-msdosdjgpp-gcc
    endif

    ifeq ($(wildcard $(DJGPP_GCC)),)
        $(error "DJGPP compiler not found.")
    endif

    CC      = $(DJGPP_GCC)
    CFLAGS  = -I$(NADIA_ROOT)include -D__OLD__ -DALLEGRO_NO_MAGIC_MAIN
    LDFLAGS = -L$(NADIA_ROOT)../lib/allegro/djgpp -lalleg
    PLATFORM_SRC := $(wildcard $(NADIA_ROOT)src/platform/old/*.c)
else
    CC      = gcc
    CFLAGS  = -I$(NADIA_ROOT)include -D__MODERN__ `sdl2-config --cflags`
    LDFLAGS = `sdl2-config --libs` -lSDL2_image -lSDL2_ttf -lm
    PLATFORM_SRC := $(wildcard $(NADIA_ROOT)src/platform/modern/*.c)
endif

CORE_SRC := $(wildcard $(NADIA_ROOT)src/core/*.c)
GRAPHICS_SRC := $(wildcard $(NADIA_ROOT)src/graphics/*.c) $(wildcard $(NADIA_ROOT)src/graphics/*.cpp)
ALL_SRC  := $(CORE_SRC) $(GRAPHICS_SRC) $(PLATFORM_SRC)

OBJDIR   := $(NADIA_ROOT)build/$(shell echo $(TARGET) | tr '[:upper:]' '[:lower:]')
OBJS     := $(patsubst $(NADIA_ROOT)src/%.c,$(OBJDIR)/%.o,$(ALL_SRC))
LIB      := $(NADIA_ROOT)lib/$(LIB_NAME)

.PHONY: all clean

all: $(LIB)

$(LIB): $(OBJS)
	@mkdir -p $(dir $@)
	ar rcs $@ $^

$(OBJDIR)/%.o: $(NADIA_ROOT)src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR) $(NADIA_ROOT)lib/*.a