# Compiler
CC ?= gcc

# Compilation flags
CFLAGS ?= -Wall -Wextra -Wpedantic -Werror -std=c99 -g3

# Directories
OUT_DIR ?= build
HEADER_DIR ?= ./inc/
SRC_DIR ?= ./src/
BIN_DIR ?= ./bin

# Executable name
TARGET ?= server

# Automatic file discovery
SOURCES := $(wildcard $(SRC_DIR)/*.c)
OBJECTS := $(SOURCES:$(SRC_DIR)/%.c=$(OUT_DIR)/%.o)

# Default target
all: $(BIN_DIR)/$(TARGET)

# Create binary executable
$(BIN_DIR)/$(TARGET): $(OBJECTS) | $(BIN_DIR)
	$(CC) $(OBJECTS) -o $@

# Compile source files
$(OUT_DIR)/%.o: $(SRC_DIR)/%.c | $(OUT_DIR)
	$(CC) $(CFLAGS) -I$(HEADER_DIR) -c $< -o $@

# Create directories
$(BIN_DIR) $(OUT_DIR):
	mkdir -p $@

# Clean build artifacts
clean:
	rm -rf $(OUT_DIR) $(BIN_DIR)

.PHONY: all clean