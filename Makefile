TARGET_EXEC := 2048
PATH_ROOT := /home/alex/Documents/Projet-2048/2048
SRC_DIR := src
BUILD_DIR := target

CXX := g++
CXXFLAGS := -I$(SRC_DIR)/HeaderFiles -fsanitize=address
NCURSES_FLAG := -lncurses
SFML_FLAG := -lsfml-graphics -lsfml-window -lsfml-system

SRCS := $(shell find $(SRC_DIR)/ -type f -name "*.cpp")
OBJS := $(SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

all: $(BUILD_DIR)/$(TARGET_EXEC)

$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(SFML_FLAG) $(NCURSES_FLAG)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)