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

OBJS = 

TARGET = utest

$(TARGET) : $(OBJS)

all: $(TARGET)

check : $(TARGET)
	@./$(TARGET) -v

recheck: clean check

# Files to keep
KEEP_FILES = Trump.ppm kiyomizudera_temple.ppm vegetables.ppm Makefile

clean:
	@$(RM) utest.o ./$(TARGET) $(OBJS)
	@find . -maxdepth 1 -type f \
		! \( -name "*.cpp" -o -name "*.hpp" -o -name "*.inl" $(foreach f,$(KEEP_FILES),-o -name $(f)) \) \
		-exec rm -f {} +

.PHONY : make clean check

make:
	@echo 'Attend a maker faire next year! now back to coding...'
	@${TRUE}