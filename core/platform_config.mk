ifeq ($(TARGET),OLD)
	# If installed as documented in the repo's readme.md, this must work.
	DJGPP_PREFIX ?= /usr/local/djgpp
	CC	:= $(DJGPP_PREFIX)/bin/i586-pc-msdosdjgpp-gcc
	CXX	:= $(DJGPP_PREFIX)/bin/i586-pc-msdosdjgpp-g++
	CFLAGS	= -I$(INCDIR) -D__OLD__ -DALLEGRO_NO_MAGIC_MAIN -O2 -std=c11 -Wall -Wextra -Wpedantic -Werror -Wshadow -Wcast-align -Wconversion -fno-common
	CXXFLAGS = -I$(INCDIR) -D__OLD__ `sdl2-config --cflags` -Wall -Wextra -Wpedantic -Werror -Wshadow -Wcast-align -Wconversion -fno-common
	LDFLAGS	= -L$(NADIA_ROOTDIR)/../lib/allegro/djgpp -lalleg -Wl,--allow-multiple-definition
	PLATFORM_SRC = $(shell find $(SRCDIR)/platform/old -type f \( -name "*.c" -o -name "*.cpp" \))
endif

ifeq ($(TARGET),MODERN)
	CC	= gcc
	CXX	= g++
	CFLAGS	= -I$(INCDIR) -D__MODERN__ `sdl2-config --cflags` -std=c11 -Wall -Wextra -Wpedantic -Werror -Wshadow -Wcast-align -Wconversion -fno-common
	CXXFLAGS = -I$(INCDIR) -D__MODERN__ `sdl2-config --cflags` -Wall -Wextra -Wpedantic -Werror -Wshadow -Wcast-align -Wconversion -fno-common
	LDFLAGS	= `sdl2-config --libs` -lSDL2_image -lSDL2_ttf -lm
	PLATFORM_SRC = $(shell find $(SRCDIR)/platform/modern -type f \( -name "*.c" -o -name "*.cpp" \))
endif
