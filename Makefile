CC = gcc
CFLAGS = -Wall -Wextra -g
LDFLAGS = 

SRC_DIR = src
BIN_DIR = bin
BUILD_DIR = build

SRCS = $(wildcard $(SRC_DIR)/*.c) # contains all the .c files
OBJS = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS)) # contains all the .o files (compiled .c files)
EXEC = $(BIN_DIR)/gene_detector

$(shell mkdir -p $(BIN_DIR) $(BUILD_DIR))

# default rule
all: $(EXEC)

# Compilation
$(EXEC): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^


$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Cleaning
clean:
	rm -rf $(BUILD_DIR)/* $(BIN_DIR)/*

# Execute
run: $(EXEC)
	./$(EXEC)

# Valgrind execution
valgrind: $(EXEC)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(EXEC)

.PHONY: all clean run valgrind