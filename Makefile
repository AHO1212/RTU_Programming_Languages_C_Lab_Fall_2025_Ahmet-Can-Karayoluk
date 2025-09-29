CC := cc
CFLAGS := -std=c11 -Wall -Wextra -Wpedantic -O2
SRC_DIR := src
BIN_DIR := bin

.PHONY: all clean lab2_1 lab2_2 lab2_3

all: lab2_1 lab2_2 lab2_3

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

lab2_1: $(SRC_DIR)/lab2_1.c | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $(BIN_DIR)/lab2_1 $(SRC_DIR)/lab2_1.c

lab2_2: $(SRC_DIR)/lab2_2.c | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $(BIN_DIR)/lab2_2 $(SRC_DIR)/lab2_2.c

lab2_3: $(SRC_DIR)/lab2_3.c | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $(BIN_DIR)/lab2_3 $(SRC_DIR)/lab2_3.c

clean:
	rm -rf $(BIN_DIR)
