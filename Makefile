TARGET_EXEC := 2048

PATH_ROOT := C:/Users/aleja/Documents/GitHub/2048

BUILD_DIR := $(PATH_ROOT)/target
SRC_DIRS := $(PATH_ROOT)/src
INCLUDE_DIR := $(PATH_ROOT)/include
LIB_DIR := $(PATH_ROOT)/lib

TARGET := $(BUILD_DIR)/sfml-app

# Build the final executable
$(TARGET): $(BUILD_DIR)/graphics.o
	g++ $(SRC_DIRS)/modele.cpp $(BUILD_DIR)/graphics.o $(SRC_DIRS)/2048.cpp -o $(TARGET) -L$(LIB_DIR) -lsfml-graphics -lsfml-window -lsfml-system

# Build graphics.o
$(BUILD_DIR)/graphics.o: $(SRC_DIRS)/graphics.cpp
	g++ -c $(SRC_DIRS)/graphics.cpp -o $(BUILD_DIR)/graphics.o -I$(INCLUDE_DIR)

# Create build directory if it doesn't exist
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Ensure build directory exists before building any targets
all: $(BUILD_DIR) $(TARGET)

clean:
	rm -rf $(BUILD_DIR)