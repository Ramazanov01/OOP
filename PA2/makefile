# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra

# Target executable
TARGET = sparse_matrix_test

# Source files (excluding main.cpp for submission)
SRCS = Sparse1D.cpp Sparse2D.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Default target - builds and runs
all: $(TARGET)
	@echo "\nRunning program..."
	@./$(TARGET)

# Link object files to create executable
$(TARGET): $(OBJS) main.o
	@echo "Linking..."
	@$(CXX) $(CXXFLAGS) -o $@ $^

# Compile source files into object files
%.o: %.cpp
	@echo "Compiling $<..."
	@$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build files
clean:
	@echo "Cleaning..."
	@rm -f $(OBJS) main.o $(TARGET)

# Phony targets
.PHONY: all clean