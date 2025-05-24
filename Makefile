# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -O2 -Wall -Iinclude
LDFLAGS = -ldl

# Source files
SRC_DIR = src
OBJ_DIR = build
SRC = $(wildcard $(SRC_DIR)/*.cpp)
OBJ = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC))

# Target
TARGET = program
# Libraries
LIBS = -lmpfr -lgmp


# Default rule
all: $(TARGET)

# Link objects to create the final binary
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS) -w

# Compile .cpp to .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(LDFLAGS) -w

# Clean up
clean:
	rm -rf $(OBJ_DIR) $(TARGET)
