# === Compiler Settings ===
CXX = g++
CC = $(CXX)

CXXFLAGS  = -pedantic -Wall -Werror -Wextra -g3 -std=c++17

# === Project Structure ===
INCLUDES_DIR = ../../../inc
SOURCES_DIR = ../../../src
LIB_DIR      = ../../../lib

ASSETS_DIR_ABS = $(abspath ../assets)

CPPFLAGS += -MMD -MP
CPPFLAGS += -I"$(INCLUDES_DIR)"
CPPFLAGS += -I"$(INCLUDES_DIR)/SFML"

LDFLAGS  += -L$(LIB_DIR)
LDFLAGS  += -Wl,-rpath=$(abspath $(LIB_DIR))  # embed absolute runtime lib path
LDLIBS   += -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

# === Target ===
TARGET = utest

OBJS = $(SOURCES_DIR)/arkanoid/box.o $(SOURCES_DIR)/arkanoid/ball.o\
	   $(SOURCES_DIR)/arkanoid/entity.o $(SOURCES_DIR)/arkanoid/block.o\
	   $(SOURCES_DIR)/arkanoid/brick.o $(SOURCES_DIR)/arkanoid/game_board.o\
	   $(SOURCES_DIR)/arkanoid/level.o $(SOURCES_DIR)/arkanoid/paddle.o\
	   $(SOURCES_DIR)/arkanoid/game_scene.o $(SOURCES_DIR)/arkanoid/input_controller.o\
	   $(SOURCES_DIR)/arkanoid/collision_detector.o $(SOURCES_DIR)/arkanoid/player.o\
	   $(SOURCES_DIR)/arkanoid/game.o $(SOURCES_DIR)/arkanoid/heart_shape.o\
	   $(SOURCES_DIR)/arkanoid/resources_and_consts.o $(SOURCES_DIR)/arkanoid/button.o\
	   $(SOURCES_DIR)/arkanoid/opening_scene.o $(SOURCES_DIR)/arkanoid/ui.o\
	   $(SOURCES_DIR)/arkanoid/game_logic.o $(SOURCES_DIR)/arkanoid/overlay_layer.o\
	   $(SOURCES_DIR)/arkanoid/high_scores.o $(SOURCES_DIR)/arkanoid/input_name.o\
	   $(SOURCES_DIR)/arkanoid/top10_scene.o $(SOURCES_DIR)/arkanoid/binary_file_high_score_storage.o\
	   $(SOURCES_DIR)/arkanoid/standard_brick.o $(SOURCES_DIR)/arkanoid/indestructible_brick.o\
	   $(SOURCES_DIR)/arkanoid/level_loader.o\
	   utest.o

# === Build Targets ===
all: $(TARGET)

$(TARGET): $(OBJS)

# check: $(TARGET)
# 	LD_LIBRARY_PATH=$(LIB_DIR) ./$(TARGET)

check: $(TARGET)
	mkdir -p assets
	cp $(ASSETS_DIR_ABS)/* assets/
	LD_LIBRARY_PATH=$(LIB_DIR) ./$(TARGET)
	

recheck: clean check

leaks: $(TARGET)
	LD_LIBRARY_PATH=$(LIB_DIR) valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./$(TARGET)

races: $(TARGET)
	LD_LIBRARY_PATH=$(LIB_DIR) valgrind --tool=helgrind ./$(TARGET)

# clean:
# 	@$(RM) $(TARGET) $(OBJS) $(DEPENDS)

clean:
	@$(RM) -r assets
	@$(RM) $(TARGET) $(OBJS) $(DEPENDS)


.PHONY: all check clean leaks races recheck

DEPENDS += $(OBJS:.o=.d)
-include $(DEPENDS)