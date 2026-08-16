include ../../engine/Makefile

NAME    = compat
SRC     = compat.c
OBJDIR  = build/$(shell echo $(TARGET) | tr '[:upper:]' '[:lower:]')
BIN     = $(OBJDIR)/$(NAME)$(EXT)

.PHONY: all clean-example

all: engine $(BIN)

engine:
	$(MAKE) -C ../../engine all TARGET=$(TARGET)

$(BIN): $(SRC)
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -o $@ $< -lengine_$(shell echo $(TARGET) | tr '[:upper:]' '[:lower:]') $(LDFLAGS) -L../../engine/lib

clean: clean-example
	rm -rf $(OBJDIR)