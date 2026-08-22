ifeq ($(TARGET),OLD)
	# If installed as documented in the repo's readme.md, this must work.
	DJGPP_PREFIX ?= /usr/local/djgpp
	CC	:= $(DJGPP_PREFIX)/bin/i586-pc-msdosdjgpp-gcc

	CFLAGS	= -I$(INCDIR) -D__OLD__ -DALLEGRO_NO_MAGIC_MAIN
	LDFLAGS	= -L$(NADIA_ROOTDIR)/../lib/allegro/djgpp -lalleg
	PLATFORM_SRC	:= $(wildcard $(SRCDIR)/old/*.c)
endif

ifeq ($(TARGET),MODERN)
	CC	= g++
	CFLAGS	= -I$(INCDIR) -D__MODERN__ `sdl2-config --cflags`
	LDFLAGS	= `sdl2-config --libs` -lSDL2_image -lSDL2_ttf -lm
	PLATFORM_SRC	:= $(wildcard $(SRCDIR)/modern/*.c)
endif

