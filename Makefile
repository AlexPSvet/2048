TARGET_EXEC := 2048

PATH_ROOT := /home/alex/Documents/Projet-2048/2048

BUILD_DIR := $(PATH_ROOT)/target
SRC_DIRS := $(PATH_ROOT)/src
INCLUDE_DIR := $(PATH_ROOT)/include
LIB_DIR := $(PATH_ROOT)/lib

TARGET := $(BUILD_DIR)/2048

$(TARGET): $(BUILD_DIR)/graphics.o $(SRC_DIRS)/modele.cpp $(SRC_DIRS)/modele.h $(SRC_DIRS)/2048.cpp
	g++ $(BUILD_DIR)/graphics.o $(SRC_DIRS)/modele.cpp $(SRC_DIRS)/modele.h $(SRC_DIRS)/2048.cpp -o $(BUILD_DIR)/$(TARGET_EXEC) -L$(LIB_DIR) -lsfml-graphics -lsfml-window -lsfml-system

$(BUILD_DIR)/graphics.o: $(SRC_DIRS)/graphics.cpp
	cd $(BUILD_DIR); g++ -c $(SRC_DIRS)/graphics.cpp -I$(INCLUDE_DIR)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

all: $(BUILD_DIR) $(TARGET)

clean:
	rm -rf $(BUILD_DIR)