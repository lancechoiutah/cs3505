# Makefile for CS 3505 Assignment 3

# --- Requirement: Variable for libpng path ---
LIBPNG = ./libpng-1.6.45

# Compiler settings
CXX = g++
CXXFLAGS = -Wall -std=c++11 -I$(LIBPNG)
LDFLAGS = -L$(LIBPNG) -lpng

# Source files
# Include all your .cpp files here
SRCS = fernPNG.cpp pngWriter.cpp point.cpp transform.cpp
OBJS = $(SRCS:.cpp=.o)

# Target executable name
TARGET = fernPNG

# Default target
all: $(TARGET)

# Link step
$(TARGET): $(OBJS)
	$(CXX) -o $@ $(OBJS) $(LDFLAGS)

# Compile step (Implicit rule for .cpp to .o)
.cpp.o:
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean target
clean:
	rm -f $(OBJS) $(TARGET)