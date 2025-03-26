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

OBJS = $(SOURCES_DIR)/bf/memory.o $(SOURCES_DIR)/bf/vm.o $(SOURCES_DIR)/bf/compiler.o $(SOURCES_DIR)/bf/console.o $(SOURCES_DIR)/bf/program.o $(SOURCES_DIR)/bf/microcode.o#$(SOURCES_DIR)/bf/operations.o $(SOURCES_DIR)/bf/validator.o $(SOURCES_DIR)/bf/CLI.o $(SOURCES_DIR)/bf/code_parser.o $(SOURCES_DIR)/bf/IO_manager.o

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

leak-check:
	valgrind ./$(TARGET)