CC = gcc
SRC_DIR := ./src
BUILD_DIR ?= ./build
FLAGS ?= -m32

SRCS := $(wildcard $(SRC_DIR)/*.c)
BUILD := $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%)

all: $(BUILD)

$(BUILD_DIR)/%: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(FLAGS) -o $@ $<

.PHONY: clean copy

clean:
	rm -rf build/*

copy:
	@mkdir -p build/
	cp ./tests/t1 build/
	cp ./tests/t2 build/

