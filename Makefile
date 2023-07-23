CC = g++

TARGET = app
INCLUDE = include
INCLUDE_PATH = src
SUB_DIR = src src/kami/core src/kami/graphics src/kami/utils src/kami/input src/kami/scene src/kami/graphics/Camera src/kami/graphics/renderer 
LIB = lib/*

CFLAGS = -std=c++17 -Wall -L. $(LIB) -I $(INCLUDE) -I $(INCLUDE_PATH)

all: $(TARGET)

$(TARGET): export VK_ICD_FILENAMES = $(pwd)/env/MoltenVK_icd.json
$(TARGET): export VK_LAYER_PATH = $(pwd)/env/explicit_layer.d
$(TARGET): $(wildcard *.cpp $(foreach fd, ${SUB_DIR}, $(fd)/*.cpp)) $(wildcard *.hpp $(foreach fd, ${SUB_DIR}, $(fd)/*.hpp))
	$(CC) $(CFLAGS) -o $(TARGET) $(wildcard *.cpp $(foreach fd, ${SUB_DIR}, $(fd)/*.cpp))

clean:
	$(RM) $(TARGET)
	echo "$(wildcard *.hpp $(foreach fd, ${SUB_DIR}, $(fd)/*.hpp))"
