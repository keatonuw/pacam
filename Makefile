# Compiler
CC := gcc

# Compiler flags
CFLAGS := $(shell sdl2-config --cflags) -g

# Linker flags
LDFLAGS := $(shell sdl2-config --libs) -lSDL2_image

# Target executable
TARGET := pacam

# Directories
SRC_DIR := src
BUILD_DIR := build

# Source files (located in the SRC_DIR)
SRC := $(wildcard $(SRC_DIR)/*.c)

# Object files (automatically generated from source files)
OBJ := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRC))

# Build rule
$(BUILD_DIR)/$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $@ $(LDFLAGS)

# Rule to compile source files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean rule
clean:
	rm -rf $(BUILD_DIR)

# Phony targets (targets that are not actually files)
.PHONY: all clean

# Default target
all: $(BUILD_DIR)/$(TARGET)
