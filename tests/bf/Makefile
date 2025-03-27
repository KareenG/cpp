CXX= g++
CC = $(CXX)

CXXFLAGS  = -pedantic -Wall -Werror -Wextra
CXXFLAGS += -g3
CXXFLAGS += -std=c++17

# CPPFLAGS = -DDEBUG
CPPFLAGS = -I$(INCLUDES_DIR)#-DBF_DEBUG

# LDFLAGS =
# LDLIBS = -lm    # link math library

INCLUDES_DIR = ../../inc
SOURCES_DIR = ../../src

OBJS = $(SOURCES_DIR)/bf/memory.o $(SOURCES_DIR)/bf/vm.o $(SOURCES_DIR)/bf/compiler.o $(SOURCES_DIR)/bf/console.o $(SOURCES_DIR)/bf/program.o $(SOURCES_DIR)/bf/microcode.o

APP_OBJS = $(OBJS) $(SOURCES_DIR)/bf/command_line_args.o
APP = $(SOURCES_DIR)/bf/run_bf

UTEST = utest

all : $(APP) $(UTEST)

$(APP) : CPPFLAGS += -DNDEBUG
$(APP) : $(APP_OBJS)

$(UTEST) : CPPFLAGS += -DBF_DEBUG
$(UTEST) : $(OBJS)

# check : CPPFLAGS += -DBF_DEBUG
# check: $(UTEST)
# 	./$(UTEST)

#recheck: clean check

clean:
	$(RM) $(UTEST) $(OBJS) $(APP) $(APP_OBJS)

.PHONY : make clean check

make:
	@echo 'Attend a maker faire next year! now back to coding...'
	@${TRUE}

leak-check : $(UTEST)
	valgrind ./$(UTEST)