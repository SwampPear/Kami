CC = g++
CFLAGS = -std=c++14 -Wall -I include -L. lib/*
TARGET = app

all: $(TARGET)

$(TARGET): export VK_ICD_FILENAMES = $(pwd)/env/MoltenVK_icd.json
$(TARGET): export VK_LAYER_PATH = $(pwd)/env/explicit_layer.d
$(TARGET): src/main.cpp
	$(CC) $(CFLAGS) -o $(TARGET) src/main.cpp

clean:
	$(RM) $(TARGET)
