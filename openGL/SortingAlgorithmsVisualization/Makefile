SRC_DIR = src
BUILD_DIR = build/debug
CC = g++
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
OBJ_NAME = play
INCLUDE_PATHS = -Iinclude
LIBRARY_PATHS = -Llibrary
COMPILER_FLAGS = -std=c++11 -Wall -O0 -g
FRAMEWORK_PATH = -F/Library/Frameworks -framework SDL2 -framework SDL2_image -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo -framework CoreFoundation
all:
	$(CC) $(COMPILER_FLAGS)  $(LIBRARY_PATHS) library/lib/libglfw.3.3.dylib  $(INCLUDE_PATHS) $(SRC_FILES) -o $(BUILD_DIR)/$(OBJ_NAME) $(FRAMEWORK_PATH)