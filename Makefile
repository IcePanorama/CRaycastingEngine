SRC_DIR=src
SRC_FILES=$(SRC_DIR)/*.c
INCL_FILES=$(SRC_DIR)/*.h
LIBS=-lraylib -lm
TARGET=main
CFLAGS=-std=c99 -Wpedantic -Wextra -Werror -Wall -Wstrict-aliasing=3 -Wwrite-strings -Wvla -Wcast-align=strict -Wstrict-prototypes -Wstringop-overflow=4 -Wno-logical-op-parentheses -Wshadow -fanalyzer
STYLE=GNU

all: clean format $(TARGET) test

fast: clean $(TARGET)

$(TARGET): 
	gcc $(SRC_FILES) -I./$(INCL_DIR) -o $(TARGET) $(LIBS) $(CFLAGS)

test: $(TARGET)
	valgrind --leak-check=yes ./$(TARGET)

clean:
	-@rm $(TARGET) 2>/dev/null || true

format: 
	clang-format -style=$(STYLE) -i $(SRC_FILES) $(INCL_FILES)
