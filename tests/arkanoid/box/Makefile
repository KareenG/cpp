# === Compiler Settings ===
CXX = g++
CC = $(CXX)

CXXFLAGS  = -pedantic -Wall -Werror -Wextra -g3 -std=c++17

# === Project Structure ===
INCLUDES_DIR = ../../../inc
SOURCES_DIR = ../../../src
LIB_DIR      = ../../../lib

CPPFLAGS += -MMD -MP
CPPFLAGS += -I"$(INCLUDES_DIR)"
CPPFLAGS += -I"$(INCLUDES_DIR)/SFML"

LDFLAGS  += -L$(LIB_DIR)
LDFLAGS  += -Wl,-rpath=$(abspath $(LIB_DIR))  # embed absolute runtime lib path
LDLIBS   += -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

# === Target ===
TARGET = utest

OBJS = $(SOURCES_DIR)/arkanoid/box/box.o $(SOURCES_DIR)/arkanoid/box/collision_detector.o\
	   $(SOURCES_DIR)/arkanoid/box/entity.o $(SOURCES_DIR)/arkanoid/box/game.o\
	   $(SOURCES_DIR)/arkanoid/box/particle.o $(SOURCES_DIR)/arkanoid/box/spatial_grid.o utest.o

# === Build Targets ===
all: $(TARGET)

$(TARGET): $(OBJS)

check: $(TARGET)
	LD_LIBRARY_PATH=$(LIB_DIR) ./$(TARGET)

recheck: clean check

leaks: $(TARGET)
	LD_LIBRARY_PATH=$(LIB_DIR) valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./$(TARGET)

races: $(TARGET)
	LD_LIBRARY_PATH=$(LIB_DIR) valgrind --tool=helgrind ./$(TARGET)

clean:
	@$(RM) $(TARGET) $(OBJS) $(DEPENDS)

.PHONY: all check clean leaks races recheck

DEPENDS += $(OBJS:.o=.d)
-include $(DEPENDS)