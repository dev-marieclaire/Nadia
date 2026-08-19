include ../../engine/Makefile

NAME    = sprite
SRC     = $(NAME).c
OBJDIR  = build/$(shell echo $(TARGET) | tr '[:upper:]' '[:lower:]')
BIN     = $(OBJDIR)/$(NAME)$(EXT)
# LIB_NAME = nadia_platform_$(shell echo $(TARGET) | tr '[:upper:]' '[:lower:]').a

.PHONY: all clean-example

all: engine $(BIN)

engine:
	$(MAKE) -C ../../engine all TARGET=$(TARGET)

$(BIN): $(SRC)
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS) -L../../engine/lib -l$(LIB_NAME)

clean: clean-example
	rm -rf $(OBJDIR)