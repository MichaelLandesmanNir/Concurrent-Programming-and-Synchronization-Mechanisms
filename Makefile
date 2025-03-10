# Define compiler and flags
CXX = g++
CXXFLAGS = -Wall -std=c++14

# Define the target executable
TARGET = ex3.out

# List all source files
SRCS = main.cpp Producer.cpp Dispatcher.cpp CoEditor.cpp ScreenManager.cpp BoundedBuffer.cpp

# Generate object files from source files
OBJS = $(SRCS:.cpp=.o)

# Default target
all: $(TARGET)

# Rule to build the target executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Rule to build object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean rule to remove built files
clean:
	rm -f $(TARGET) $(OBJS)

# Run the program
run: $(TARGET)
	./$(TARGET) config.txt
