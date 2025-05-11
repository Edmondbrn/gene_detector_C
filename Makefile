CC = gcc
CFLAGS = -Wall -Wextra -g -I./include
LDFLAGS = 

SRC_DIR = src
BIN_DIR = bin
BUILD_DIR = build

# Get all .c files in the src folder
SRCS = $(shell find $(SRC_DIR) -name "*.c")
# Convert c files into object files
OBJS = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))
EXEC = $(BIN_DIR)/gene_detector

$(shell mkdir -p $(BIN_DIR) $(BUILD_DIR)/utils)

# Default rule
all: $(EXEC)

# Compilation
$(EXEC): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

# Compilation of object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Cleaning
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)/*

# Execution
run: $(EXEC)
	./$(EXEC)

# Valgrind execution
valgrind: $(EXEC)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(EXEC)

.PHONY: all clean run valgrind