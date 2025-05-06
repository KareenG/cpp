CXX= g++
CC = $(CXX)

CXXFLAGS  = -pedantic -Wall -Werror -Wextra
CXXFLAGS += -g3
CXXFLAGS += -std=c++20

INCLUDES_DIR = ../../inc
SOURCES_DIR = ../../src

CPPFLAGS += -MMD -MP
CPPFLAGS += -I$(INCLUDES_DIR)

TARGET = utest

OBJS = $(SOURCES_DIR)/mt/thread_pool.o utest.o

all: $(TARGET)

check : $(TARGET)
	./$(TARGET)

recheck: clean check

leaks: $(TARGET)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./$(TARGET)

races: $(TARGET)
	valgrind --tool=helgrind ./$(TARGET)

clean:
	@$(RM) ./$(TARGET) $(OBJS) $(DEPENDS)

.PHONY: clean check leaks races

$(TARGET) : $(OBJS)

DEPENDS += $(OBJS:.o=.d)
-include $(DEPENDS)