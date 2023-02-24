# Copyright 2023 Camilo Suárez Sandí

# Project

PROJECT_NAME = project
PROJECT_LANGUAGE = C

# Language

C = clang
C_VERSION = -std=gnu17
C_EXT = c

CPP = clang++
CPP_VERSION = -std=gnu++17
CPP_EXT = cpp

ifeq ($(PROJECT_LANGUAGE),C)
CX = $(C)
CX_VERSION = $(C_VERSION)
CX_EXT = $(C_EXT)
endif
ifeq ($(PROJECT_LANGUAGE),C++)
CX = $(CPP)
CX_VERSION = $(CPP_VERSION)
CX_EXT = $(CPP_EXT)
endif

# Flags

FLAGS = $(CX_VERSION) -Wall -Werror -Wextra

# Directories

SRC_DIR = src
TEST_DIR = test
BUILD_DIR = build
BIN_DIR = bin

# Files

SRC_FILES = $(shell find $(SRC_DIR) -name *.$(CX_EXT))
SRC_BUILD_FILES = $(patsubst $(SRC_DIR)/%.$(CX_EXT),$(BUILD_DIR)/$(SRC_DIR)/%.$(CX_EXT).o,$(SRC_FILES))

TEST_FILES = $(shell find $(TEST_DIR) -name *.$(CX_EXT))
TEST_BUILD_FILES = $(patsubst $(TEST_DIR)/%.$(CX_EXT),$(BUILD_DIR)/$(TEST_DIR)/%.$(CX_EXT).o,$(TEST_FILES))

# Targets

build: FLAGS += -I$(SRC_DIR)
build: $(BIN_DIR)/$(SRC_DIR)/$(PROJECT_NAME)

$(BIN_DIR)/$(SRC_DIR)/$(PROJECT_NAME): $(SRC_BUILD_FILES) | $(BIN_DIR)/$(SRC_DIR)/
	$(CX) $(FLAGS) $^ -o $@

$(BUILD_DIR)/$(SRC_DIR)/%.$(CX_EXT).o: $(SRC_DIR)/%.$(CX_EXT) | $(dir $(SRC_BUILD_FILES))
	$(CX) $(FLAGS) -c $^ -o $@

test: FLAGS += -I$(SRC_DIR) -DTEST
test: $(BIN_DIR)/$(TEST_DIR)/$(PROJECT_NAME)
	$(BIN_DIR)/$(TEST_DIR)/$(PROJECT_NAME) $(ARGS)

$(BIN_DIR)/$(TEST_DIR)/$(PROJECT_NAME): $(SRC_BUILD_FILES) $(TEST_BUILD_FILES) | $(BIN_DIR)/$(TEST_DIR)/
	$(CX) $(FLAGS) $^ -o $@

$(BUILD_DIR)/$(TEST_DIR)/%.$(CX_EXT).o: $(TEST_DIR)/%.$(CX_EXT) | $(dir $(TEST_BUILD_FILES))
	$(CX) $(FLAGS) -c $^ -o $@

run: build
	$(BIN_DIR)/$(SRC_DIR)/$(PROJECT_NAME) $(ARGS)

.PRECIOUS: %/
%/:
	mkdir -p $@

clean:
	rm -fr $(BIN_DIR)/ $(BUILD_DIR)/

asan: FLAGS += -fsanitize=address
asan: build

tsan: FLAGS += -fsanitize=thread
tsan: build

tasan: FLAGS += -fsanitize=address
tasan: test

ttsan: FLAGS += -fsanitize=thread
ttsan: test

install:
	sudo apt install cpplint

lint:
	cpplint $(SRC_FILES) $(TEST_FILES)
