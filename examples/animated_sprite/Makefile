NAME = animated_sprite
ENGINE_SRC_DIR = ./../../src

# BUILD DIRS
BUILD_MODERN = ./build/modern
BUILD_OLD = ./build/dos

## Default target option:
TARGET ?= MODERN

ifeq ($(TARGET), OLD)
    DJGPP_GCC := $(shell which i586-pc-msdosdjgpp-g++ 2>/dev/null)

    ifeq ($(DJGPP_GCC),)
        DJGPP_GCC := /usr/local/djgpp/bin/i586-pc-msdosdjgpp-g++
    endif

    ifeq ($(wildcard $(DJGPP_GCC)),)
        $(error "DJGPP compiler not found.")
    endif

	CC		= $(DJGPP_GCC)
	CFLAGS	= -I./../../include -I./../../include/allegro/include -D__DJGPP__
	LDFLAGS	= -L./../../engine/include/allegro/lib/djgpp -lalleg
	EXT		= .exe
	OBJDIR	= $(BUILD_DOS)
	IMG		= *.bmp
else
	CC		= g++
	CFLAGS	= -I./../../include `sdl2-config --cflags`
	LDFLAGS	= `sdl2-config --libs` -lSDL2_image -lm
	EXT		=
	OBJDIR	= $(BUILD_MODERN)
	IMG		= *.png
endif

## Sources
ENGINE_SRC	= $(shell find ./../../src -type f \( -name "*.c" -o -name "*.cpp" \))
EXAMPLE_SRC	= $(NAME).cpp
SRC		= $(EXAMPLE_SRC) $(ENGINE_SRC)

## Objects
ENGINE_OBJ	:= $(patsubst $(ENGINE_SRC_DIR)/%.c, $(OBJDIR)/%.o, $(filter %.c, $(ENGINE_SRC)))
ENGINE_OBJ	+= $(patsubst $(ENGINE_SRC_DIR)/%.cpp, $(OBJDIR)/%.o, $(filter %.cpp, $(ENGINE_SRC)))
EXAMPLE_OBJ	= $(OBJDIR)/$(NAME).o
OBJ		= $(EXAMPLE_OBJ) $(ENGINE_OBJ)

BIN		= $(OBJDIR)/$(NAME)$(EXT)

# debug:
# 	@echo "=========================================="
# 	@echo "TARGET: $(TARGET)"
# 	@echo "OBJDIR: $(OBJDIR)"
# 	@echo "ENGINE_SRC_DIR: $(ENGINE_SRC_DIR)"
# 	@echo "Main source: $(EXAMPLE_SRC)"
# 	@echo ""
# 	@echo "Engine sources found: $(words $(ENGINE_SRC))"
# 	@echo "Engine object files to build: $(words $(ENGINE_OBJ))"
# 	@echo "Total object files: $(words $(OBJ))"
# 	@echo ""
# 	@echo "First 5 engine objects:"
# 	@echo "$(ENGINE_OBJ)" | tr ' ' '\n' | head -5
# 	@echo ""
# 	@echo "Link command will be:"
# 	@echo "  $(CC) -o $(BIN) $(OBJ) $(LDFLAGS)"
# 	@echo "=========================================="

.PHONY = all clean compile move

all: $(BIN)

$(BIN): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

$(OBJDIR)/%.o: $(ENGINE_SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/%.o: $(ENGINE_SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/$(NAME).o: $(NAME).cpp
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

copy:
	cp $(IMG) $(OBJDIR)

clean:
	rm -fr $(OBJDIR) $(BIN)

compile: all
	@echo "Compilation succeded. Binary file location: $(BIN)"

# compile:
# 	mkdir -p $(BUILD)
# 	cp ./*.png $(BUILD)

# 	g++ $(SRC) $(INCLUDE) -g -o $(OUT) $(LFLAGS)

# run:
# 	cd ./build && ./$(BIN)
