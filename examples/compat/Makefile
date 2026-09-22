# ============================================================
#  Example Makefile – builds an executable against Nadia
#  Usage: make TARGET=MODERN   (or OLD)
# ============================================================

TARGET ?= MODERN
TARGET_LOWERCASE := $(shell echo $(TARGET) | tr '[:upper:]' '[:lower:]')

NADIA_ROOTDIR := $(realpath ../../core)
INCDIR        := $(NADIA_ROOTDIR)/include
LIBDIR        := $(NADIA_ROOTDIR)/../build/lib

# Executable extension
ifeq ($(OS),Windows_NT)
    EXT := .exe
else
    EXT :=
endif

# Example‑specific variables (change per example)
NAME    := compat
SRC     := $(NAME).c
OBJDIR  := ../../build/bin/$(NAME)/$(TARGET_LOWERCASE)
BIN     := $(OBJDIR)/$(NAME)$(EXT)

# Include platform config (sets CFLAGS, LDFLAGS)
include $(NADIA_ROOTDIR)/platform_config.mk

.PHONY: all clean engine

all: engine $(BIN)

# Build engine first
engine:
	$(MAKE) -C $(NADIA_ROOTDIR) TARGET=$(TARGET)

# Link example
$(BIN): $(SRC)
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -o $@ $< \
		-I$(INCDIR) \
		-L$(LIBDIR) \
		-lnadia_platform_$(TARGET_LOWERCASE) \
		$(LDFLAGS)

exec:
	ifeq($(TARGET),MODERN)
		$(BIN)
	else
		dosbox $(BIN)
	endif

clean:
	rm -rf $(OBJDIR)
