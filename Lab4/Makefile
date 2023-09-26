CC=gcc
CFLAGS=-c -Wall -I./inc
LDFLAGS=-lunistring
SRC_DIR=./src
BUILD_DIR=./build

SOURCES=$(wildcard $(SRC_DIR)/*.c)
OBJECTS=$(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SOURCES))
DEPS=$(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.d,$(SOURCES))
EXECUTABLE=$(BUILD_DIR)/Lab4

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $< -o $@
	$(CC) -MM $< > $(BUILD_DIR)/$*.d

-include $(DEPS)

clean:
	rm -rf $(BUILD_DIR)/*.o $(BUILD_DIR)/*.d $(EXECUTABLE)

.PHONY: clean
