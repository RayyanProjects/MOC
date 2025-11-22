CC      := g++
CFLAGS  := -std=c++20 -Wall -Wextra -g

SRC_DIR := src
BUILD_DIR := build
TARGET := $(BUILD_DIR)/moc
EXAMPLE := $(wildcard examples/*.moc)

# Collect all .c files
SRC := $(wildcard $(SRC_DIR)/**/*.cpp) $(wildcard $(SRC_DIR)/*.cpp)
all: $(TARGET)

$(TARGET): $(SRC) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(SRC) -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)

run: $(TARGET)
	./$(TARGET) $(EXAMPLE)
