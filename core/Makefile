# ============================================================
#  Nadia Engine – Core Makefile (Simplified)
#  Usage: make TARGET=MODERN   (or OLD)
# ============================================================

MAKEFILE_DIR := $(realpath $(dir $(abspath $(lastword $(MAKEFILE_LIST)))))
NADIA_ROOTDIR := $(MAKEFILE_DIR)

# ----------------------------------------------------------------------
#  Directories
# ----------------------------------------------------------------------
INCDIR        := $(NADIA_ROOTDIR)/include
SRCDIR        := $(NADIA_ROOTDIR)/src
BUILDDIR      := $(NADIA_ROOTDIR)/../build/lib
OBJDIR        := $(BUILDDIR)/obj

# ----------------------------------------------------------------------
#  Target selection
# ----------------------------------------------------------------------
TARGET        ?= MODERN
TARGET_LOWERCASE := $(shell echo $(TARGET) | tr '[:upper:]' '[:lower:]')
PLATFORM_DIR  := $(SRCDIR)/platform/$(TARGET_LOWERCASE)

# ----------------------------------------------------------------------
#  Source files
# ----------------------------------------------------------------------
COMMON_SRC    := $(wildcard $(SRCDIR)/common/*.c)
GRAPHICS_C    := $(wildcard $(SRCDIR)/graphics/*.c)
GRAPHICS_CPP  := $(wildcard $(SRCDIR)/graphics/*.cpp)
PLATFORM_SRC  := $(wildcard $(PLATFORM_DIR)/*.c)

ALL_C         := $(COMMON_SRC) $(GRAPHICS_C) $(PLATFORM_SRC)
ALL_CPP       := $(GRAPHICS_CPP)

# Object files (flattened – no subdirs)
C_OBJ         := $(addprefix $(OBJDIR)/, $(notdir $(ALL_C:.c=.o)))
CPP_OBJ       := $(addprefix $(OBJDIR)/, $(notdir $(ALL_CPP:.cpp=.o)))
OBJFILES      := $(C_OBJ) $(CPP_OBJ)

# ----------------------------------------------------------------------
#  Library output
# ----------------------------------------------------------------------
LIB_NAME      := libnadia_platform_$(TARGET_LOWERCASE).a
OUT           := $(BUILDDIR)/$(LIB_NAME)

# ----------------------------------------------------------------------
#  Compiler flags
# ----------------------------------------------------------------------
BASE_CFLAGS   := -I$(INCDIR) -I$(PLATFORM_DIR) -MMD -MP -Wall -Wextra

include $(NADIA_ROOTDIR)/platform_config.mk

CFLAGS    += $(BASE_CFLAGS)
CXXFLAGS  += $(BASE_CFLAGS)

# ----------------------------------------------------------------------
#  Debug output (useful for troubleshooting)
# ----------------------------------------------------------------------
$(info ===== BUILD CONFIG =====)
$(info TARGET = $(TARGET))
$(info PLATFORM_DIR = $(PLATFORM_DIR))
$(info ALL_C = $(ALL_C))
$(info ALL_CPP = $(ALL_CPP))
$(info C_OBJ = $(C_OBJ))
$(info CPP_OBJ = $(CPP_OBJ))
$(info OBJFILES = $(OBJFILES))
$(info OUT = $(OUT))
$(info =======================)

.PHONY: all clean

all: $(OUT)

ifeq ($(strip $(PLATFORM_SRC)),)
$(error "PLATFORM_SRC is empty. Check that $(PLATFORM_DIR) exists and contains .c files.")
endif

# ----------------------------------------------------------------------
#  Build rules
# ----------------------------------------------------------------------

# Link – create static library
$(OUT): $(OBJFILES)
	@mkdir -p $(dir $@)
	@echo "Creating archive: $@"
	ar rcs $@ $^

# Tell make where to find .c and .cpp files
vpath %.c $(SRCDIR)/common $(SRCDIR)/graphics $(PLATFORM_DIR)
vpath %.cpp $(SRCDIR)/graphics

# Compile C sources
$(OBJDIR)/%.o: %.c
	@mkdir -p $(OBJDIR)
	@echo "Compiling C: $<"
	$(CC) $(CFLAGS) -c $< -o $@

# Compile C++ sources
$(OBJDIR)/%.o: %.cpp
	@mkdir -p $(OBJDIR)
	@echo "Compiling C++: $<"
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean
clean:
	rm -fr $(NADIA_ROOTDIR)/../build/

# Include auto-dependencies
-include $(OBJFILES:.o=.d)
