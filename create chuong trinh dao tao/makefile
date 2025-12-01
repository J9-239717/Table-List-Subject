# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -g
TARGET = myprogram

# Source files
SRCS = $(wildcard main/*.c) $(wildcard module/Topo/*.c)

# Default target
.PHONY: all
all: $(TARGET)

# Build the program
$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET)

# Clean build artifacts
.PHONY: clean
clean:
	rm -f $(TARGET)

# Force rebuild
.PHONY: rebuild
rebuild: clean all

# Run the program
.PHONY: run
run: $(TARGET)
	./$(TARGET)