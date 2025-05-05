CXX= g++
CC = $(CXX)

CXXFLAGS  = -pedantic -Wall -Werror -Wextra
CXXFLAGS += -g3
CXXFLAGS += -std=c++20

# CPPFLAGS = -DDEBUG
CPPFLAGS = -I$(INCLUDES_DIR)

# LDFLAGS =
# LDLIBS = -lm    # link math library

INCLUDES_DIR = ../../inc
SOURCES_DIR = ../../src

OBJS = $(SOURCES_DIR)/mt/thread_pool.o

TARGET = utest

$(TARGET) : $(OBJS)

all: $(TARGET)

check : $(TARGET)
	@./$(TARGET) -v

recheck: clean check

clean:
	$(RM) $(TARGET) $(OBJS)

.PHONY : make clean check

make:
	@echo 'Attend a maker faire next year! now back to coding...'
	@${TRUE}

# make leak-check
leak-check:
	valgrind --leak-check=full ./utest