SRC_DIR=src
SRC_FILES=$(SRC_DIR)/*.c
#INCL_DIR=include
#INCL_FILES=$(INCL_DIR)/*.h
LIBS=raylib
TARGET=main
CFLAGS=-std=c99 -Wpedantic -Wextra -Werror -Wall 
STYLE=GNU

all: clean format $(TARGET) test

$(TARGET): 
	gcc $(SRC_FILES) -I./$(INCL_DIR) -o $(TARGET) -l$(LIBS) $(CFLAGS)

test: $(TARGET)
	valgrind --leak-check=yes ./$(TARGET)

clean:
	-@rm $(TARGET) 2>/dev/null || true

format: 
	clang-format -style=$(STYLE) -i $(SRC_FILES) $(INCL_FILES)
