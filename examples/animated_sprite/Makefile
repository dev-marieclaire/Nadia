TARGET	?= MODERN

NADIA_ROOTDIR	:= $(realpath ../../core)
include ../../core/platform_config.mk

NAME	= animated_sprite
INCDIR	= $(NADIA_ROOTDIR)/include
SRC	= $(NAME).c
OBJDIR	= build/$(TARGET_LOWERCASE)
BIN	= $(OBJDIR)/$(NAME)$(EXT)

.PHONY: all clean engine

all: engine $(BIN)

engine:
	$(MAKE) -C $(NADIA_ROOTDIR) all TARGET=$(TARGET)

$(BIN): $(SRC)
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -o $@ $< -I$(INCDIR) -L$(NADIA_ROOTDIR)/build -lnadia_platform_$(shell echo $(TARGET) | tr '[:upper:]' '[:lower:]') $(LDFLAGS)

clean:
	rm -rf $(OBJDIR)

