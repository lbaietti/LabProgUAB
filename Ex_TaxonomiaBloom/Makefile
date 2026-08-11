CC := gcc
TARGET := programa

SRC_DIR := src
INC_DIR := include
BUILD_DIR := build

CFLAGS := -Wall -Wextra -std=c11 -I$(INC_DIR) -MMD -MP
LDFLAGS :=
LDLIBS :=

SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))
DEPS := $(OBJS:.o=.d)

.PHONY: all programa run clean rebuild

all: $(OBJS)

programa: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf $(BUILD_DIR) $(TARGET)

rebuild: clean all

-include $(DEPS)
