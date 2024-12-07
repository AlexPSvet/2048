TARGET_EXEC := 2048
PATH_ROOT := /home/andresfsanchez0310/Documents/2048
SRC_DIR := $(PATH_ROOT)/src
BUILD_DIR := $(PATH_ROOT)/target
INCLUDE := $(PATH_ROOT)/include
LIB := $(PATH_ROOT)/lib

CXX := g++
CXXFLAGS := -I$(SRC_DIR)/HeaderFiles
NCURSES_FLAG := -lncurses
SFML_FLAG := -lsfml-graphics -lsfml-window -lsfml-system

SRCS := $(shell find $(SRC_DIR) -type f -name "*.cpp")
OBJS := $(SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

all: $(TARGET_EXEC)

$(TARGET_EXEC): $(OBJS)
	@mkdir -p $(dir $@)
	$(CXX) $(NCURSES_FLAG) -o $@ $^ $(CXXFLAGS) $(SFML_FLAG)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) $(TARGET_EXEC)

.PHONY: all clean
