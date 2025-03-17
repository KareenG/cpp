CXX= g++
CC = $(CXX)

CXXFLAGS  = -pedantic -Wall -Werror -Wextra
CXXFLAGS += -g3
CXXFLAGS += -std=c++17

# CPPFLAGS = -DDEBUG
CPPFLAGS = -I$(INCLUDES_DIR)

# LDFLAGS =
# LDLIBS = -lm    # link math library

INCLUDES_DIR = ../../inc
SOURCES_DIR = ../../src

OBJS = $(SOURCES_DIR)/basic/rational.o

TARGET = utest


$(TARGET) : $(OBJS)

all: $(TARGET)

check : $(TARGET)
	@./$(TARGET) -v

recheck: clean check

clean:
	@$(RM) utest.o ./$(TARGET) $(OBJS)

.PHONY : make clean check

make:
	@echo 'Attend a maker faire next year! now back to coding...'
	@${TRUE}