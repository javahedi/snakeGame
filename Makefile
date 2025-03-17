# Compiler and flags
CXX = clang++
CXXFLAGS = -std=c++17 -Iinclude
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

# Source and object files
SRC_DIR = src
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES = $(SRC_FILES:.cpp=.o)

# Executable name
TARGET = play

# Default target
all: $(TARGET)

# Link object files to create the executable
$(TARGET): $(OBJ_FILES)
	$(CXX) $(OBJ_FILES) -o $(TARGET) $(LDFLAGS)

# Compile source files into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(OBJ_FILES) $(TARGET)

# Run the executable
run: $(TARGET)
	./$(TARGET)

# Phony targets
.PHONY: all clean run