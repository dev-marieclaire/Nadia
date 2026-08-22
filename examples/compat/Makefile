NADIA_ROOTDIR	:= $(realpath ../../engine)

include ../../engine/platform_config.mk

NAME	= compat
INCDIR	= $(NADIA_ROOTDIR)/include
SRC	= $(NAME).c
OBJDIR	= build/$(shell echo $(TARGET) | tr '[:upper:]' '[:lower:]')
BIN	= $(OBJDIR)/$(NAME)$(EXT)

TARGET	?= MODERN

.PHONY: all clean engine

all: $(BIN)

engine:
	$(MAKE) -C $(NADIA_ROOTDIR) all TARGET=$(TARGET)

$(BIN): $(SRC)
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -o $@ $< -I$(INCDIR) -L$(NADIA_ROOTDIR)/build -lnadia_platform_$(shell echo $(TARGET) | tr '[:upper:]' '[:lower:]') $(LDFLAGS)

clean:
	rm -rf $(OBJDIR)
