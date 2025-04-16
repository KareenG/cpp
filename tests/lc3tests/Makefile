CXX = g++
CC = $(CXX)

CXXFLAGS = -pedantic -Wall -Werror -Wextra
CXXFLAGS += -g3
CXXFLAGS += -std=c++17

CPPFLAGS += -I$(INCLUDES_DIR)

INCLUDES_DIR = ../../inc
SOURCES_DIR = ../../src

OBJS = $(SOURCES_DIR)/lc3/loader.o $(SOURCES_DIR)/lc3/program_loader.o $(SOURCES_DIR)/lc3/memory.o
OBJS += $(SOURCES_DIR)/lc3/alu.o $(SOURCES_DIR)/lc3/console.o $(SOURCES_DIR)/lc3/cpu.o
OBJS += $(SOURCES_DIR)/lc3/decoder.o $(SOURCES_DIR)/lc3/program_counter.o $(SOURCES_DIR)/lc3/registers.o
OBJS += $(SOURCES_DIR)/lc3/trap_handler.o $(SOURCES_DIR)/lc3/decoder_detail/bits.o $(SOURCES_DIR)/lc3/decoder_detail/bit_manipulations.o
OBJS += $(SOURCES_DIR)/lc3/utility.o $(SOURCES_DIR)/lc3/utility.o $(SOURCES_DIR)/lc3/control_unit.o
OBJS += $(SOURCES_DIR)/lc3/lc3_exceptions.o $(SOURCES_DIR)/lc3/terminal_io.o

UTEST = lc3tests

all : $(UTEST)

$(UTEST): CPPFLAGS += -DBF_DEBUG
$(UTEST): $(OBJS)

check: $(UTEST)
	./$(UTEST)

leak-check :$(UTEST)
	valgrind ./$(UTEST)

clean:
	$(RM) $(UTEST) $(OBJS)