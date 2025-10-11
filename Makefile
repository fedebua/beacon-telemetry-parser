CC := gcc
CFLAGS := -Wall -DDEBUG_PRINTF
TARGET := main

# Automatically include all .c files in the directory
SRC := $(wildcard *.c)
OBJ := $(SRC:.c=.o)

all: $(TARGET)

# Link all object files into the final binary
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET)

# Compile each .c file into an object file
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean
