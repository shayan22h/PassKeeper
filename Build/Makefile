# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++11 -Wall

# Define directories
OUTPUT_DIR = ./Output

# Include directories
INCLUDES = -I/usr/local/include

# Libraries
LIBS = -L/usr/local/lib -ltinyxml2

# Source files
SRCS = ../main.cpp

# Object files
OBJS = $(patsubst ../%.cpp,$(OUTPUT_DIR)/%.o,$(SRCS))

# Executable name
EXEC = $(OUTPUT_DIR)/main

# Default target
all: $(EXEC)
	@echo "Building all: $(EXEC)"

# Rule to link the executable
$(EXEC): $(OBJS)
	@echo "Linking $(EXEC) from $(OBJS)"
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ $^ $(LIBS)
	@echo "Finished linking $(EXEC)"

# Rule to compile source files into object files
$(OUTPUT_DIR)/%.o: ../%.cpp
	@mkdir -p $(OUTPUT_DIR)
	@echo "Compiling $< to $@"
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@
	@echo "Finished compiling $<"

# Rule to clean the build directory
clean:
	@echo "Cleaning up..."
	rm -rf $(OUTPUT_DIR)
	@echo "Cleaned up."

# Phony targets
.PHONY: all clean
