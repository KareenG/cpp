CXX= g++
CC = $(CXX)

CXXFLAGS  = -pedantic -Wall -Werror -Wextra
CXXFLAGS += -g3
CXXFLAGS += -std=c++17

# CPPFLAGS = -DDEBUG
CPPFLAGS = -I$(INCLUDES_DIR) -DDDEBUG

# LDFLAGS =
# LDLIBS = -lm    # link math library

INCLUDES_DIR = ../../inc
SOURCES_DIR = ../../src

OBJS = 

# APP_OBJS = $(OBJS) $(SOURCES_DIR)/bf/command_line_args.o
# APP = $(SOURCES_DIR)/bf/run_bf

UTEST = utest

all : $(UTEST) #$(APP) 

# $(APP) : CPPFLAGS += -DNDEBUG
# $(APP) : $(APP_OBJS)

$(UTEST) : CPPFLAGS += -DDEBUG
$(UTEST) : $(OBJS)

# check : CPPFLAGS += -DBF_DEBUG
# check: $(UTEST)
# 	./$(UTEST)

#recheck: clean check

# $(APP) $(APP_OBJS)
clean:
	$(RM) $(UTEST) $(OBJS)

.PHONY : make clean check

make:
	@echo 'Attend a maker faire next year! now back to coding...'
	@${TRUE}

leak-check : $(UTEST)
	valgrind ./$(UTEST)