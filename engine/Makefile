NADIA_ROOTDIR := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))

INCDIR = $(NADIA_ROOTDIR)include
SRCDIR = $(NADIA_ROOTDIR)src

#Output lib filename.
LIB_NAME = libnadia_platform_$(shell echo $(TARGET) | tr '[:upper:]' '[:lower:]').a

# Sets if undefined.
TARGET	?= MODERN

include platform_config.mk

CORE_SRC	:= $(wildcard $(SRCDIR)/core/*.c)
GRAPHICS_SRC	:= $(wildcard $(SRCDIR)/graphics/*.c) $(wildcard $(SRCDIR)/graphics/*.cpp)

BUILDDIR	= $(NADIA_ROOTDIR)build
OBJDIR		:= $(BUILDDIR)/obj/$(shell echo $(TARGET) | tr '[:upper:]' '[:lower:]')

ALL_SRCFILES	:= $(CORE_SRC) $(GRAPHICS_SRC) $(PLATFORM_SRC)

C_SRC	:= $(filter %.c,$(ALL_SRCFILES))
CPP_SRC	:= $(filter %.cpp,$(ALL_SRCFILES))

C_OBJ := $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(C_SRC))
CPP_OBJ := $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(CPP_SRC))

OBJFILES	:= $(C_OBJ) $(CPP_OBJ)
OUT		:= $(BUILDDIR)/$(LIB_NAME)

$(info === DEBUG ===)
$(info CC=$(CC))
$(info CXX=$(CXX))
$(info CFLAGS=$(CFLAGS))
$(info CXXFLAGS=$(CXXFLAGS))
$(info MAKEFILE_LIST = $(MAKEFILE_LIST))
$(info lastword = $(lastword $(MAKEFILE_LIST)))
$(info NADIA_ROOTDIR = $(NADIA_ROOTDIR))
$(info SRCDIR = $(SRCDIR))
$(info BUILDDIR = $(BUILDDIR))
$(info OBJDIR = $(OBJDIR))
$(info OUT = $(OUT))
$(info ALL_SRCFILES = $(ALL_SRCFILES))
$(info OBJFILES = $(OBJFILES))
$(info === END DEBUG ===)

.PHONY: all clean

all: $(OUT)

$(OUT): $(OBJFILES)
	@mkdir -p $(dir $@)
	ar rcs $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -fr $(BUILDDIR)
