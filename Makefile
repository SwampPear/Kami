CC = g++

TARGET = app
INCLUDE = include
LIB = lib/*

CFLAGS = -std=c++14 -Wall -I $(INCLUDE) -L. $(LIB)

all: $(TARGET)

$(TARGET): export VK_ICD_FILENAMES = $(pwd)/env/MoltenVK_icd.json
$(TARGET): export VK_LAYER_PATH = $(pwd)/env/explicit_layer.d
$(TARGET): src/*.cpp src/*.hpp
	$(CC) $(CFLAGS) -o $(TARGET) src/*.cpp

clean:
	$(RM) $(TARGET)
