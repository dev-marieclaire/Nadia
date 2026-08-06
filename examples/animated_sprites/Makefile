SRCDIR = ../../src/
SRC = $(SRCDIR)*.cpp $(SRCDIR)*.c $(SRCDIR)**/*.c ./*.cpp
INCLUDE = -I../../include/
BUILD = ./build
OUT = $(BUILD)/sprite
LFLAGS = `pkg-config --cflags --libs sdl2 SDL2_image`

all: compile

clean:
	rm -fr ./{build,src}/*.o

compile:
	mkdir -p $(BUILD)
	cp ./*.png $(BUILD)

	g++ $(SRC) $(INCLUDE) -g -o $(OUT) $(LFLAGS)

run:
	cd ./build && SDL_VIDEODRIVER=x11 ./sprite