CXX = g++
CC = $(CXX)

INCLUDES_DIR = ../../../inc
SOURCES_DIR = ../../../src

CXXFLAGS = -pedantic -Wall -Werror -Wextra -g3 -std=c++17
CPPFLAGS = -DDEBUG -I$(INCLUDES_DIR)

OBJS = utest.o basic_math.o
TARGET = utest.out

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

check: $(TARGET)
	@./$(TARGET) -v

clean:
	@$(RM) ./$(TARGET) $(OBJS)

# Compile test file
utest.o: utest.cpp $(INCLUDES_DIR)/mu_test.h $(INCLUDES_DIR)/basic_math.hpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c utest.cpp -o utest.o

# Compile basic_math
basic_math.o: $(SOURCES_DIR)/basic_math.cpp $(INCLUDES_DIR)/basic_math.hpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $(SOURCES_DIR)/basic_math.cpp -o basic_math.o

.PHONY: all clean check