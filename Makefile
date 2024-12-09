TARGET_EXEC := 2048
PATH_ROOT := /home/andresfsanchez0310/Documents/2048
SRC_DIR := $(PATH_ROOT)/src
BUILD_DIR := $(PATH_ROOT)/target
INCLUDE := $(PATH_ROOT)/include
LIB := $(PATH_ROOT)/lib

CXX := g++
CXXFLAGS := -I$(SRC_DIR)/HeaderFiles -fsanitize=address
NCURSES_FLAG := -lncurses
SFML_FLAG := -lsfml-graphics -lsfml-window -lsfml-system

SRCS := $(shell find $(SRC_DIR) -type f -name "*.cpp")
OBJS := $(SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

all: $(BUILD_DIR)/$(TARGET_EXEC)

$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(SFML_FLAG) $(NCURSES_FLAG)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(NCURSES_FLAG)

clean:
	rm -rf $(BUILD_DIR) $(TARGET_EXEC)

.PHONY: all clean