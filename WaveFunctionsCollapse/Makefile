SRC_DIR = src
BUILD_DIR = build/debug
CC = g++
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
OBJ_NAME = play
INCLUDE_PATHS = -Iinclude
COMPILER_FLAGS = -std=c++17 -Wall -O0 -g
FRAMEWORK_PATH = -F/Library/Frameworks -framework SDL2 -framework SDL2_image

all:
	$(CC) $(COMPILER_FLAGS)  $(INCLUDE_PATHS) $(SRC_FILES) -o $(BUILD_DIR)/$(OBJ_NAME) $(FRAMEWORK_PATH)