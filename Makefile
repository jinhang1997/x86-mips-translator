# build paths
SRC_DIR := ./src
INC_DIR := ./include
OBJ_DIR := ./build/obj
BUILD_DIR := ./build
TESTS_DIR := ./tests
BUILD := $(BUILD_DIR)/xmt

# build options
CC = gcc
LD = gcc
CFLAGS ?= -m32 -I $(INC_DIR)
LFLAGS ?= -m32 -O2

# build components
SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# compile each code file into objects
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $<

# link all objects to executable
$(BUILD): $(OBJS)
	$(LD) $(LFLAGS) -o $@ $^

# some convnient rules
.PHONY: clean copy run runarg

# the file to analyze, in which $(RUNFILE) is defined
include Makefile.runfile

# flags to run xmt
#RUNFLAGS := $(RUNFILE)

run: $(BUILD)
	$(BUILD) $(RUNFILE)

# run xmt with arguments
# $(RUN) is given in command line like: make run RUN=t1
runarg: $(BUILD)
	$(BUILD) $(TESTS_DIR)/$(RUN)

# clean the project
clean:
	rm -rf build/*

