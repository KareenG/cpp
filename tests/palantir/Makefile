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

OBJS = $(SOURCES_DIR)/palantir/encryption/atbash.o $(SOURCES_DIR)/palantir/encryption/caesar.o $(SOURCES_DIR)/palantir/encryption/rot13.o $(SOURCES_DIR)/palantir/encryption/vigenere.o \
	   $(SOURCES_DIR)/palantir/encryption/null_encryption.o $(SOURCES_DIR)/palantir/message_source/console_in.o $(SOURCES_DIR)/palantir/message_source/file_source.o $(SOURCES_DIR)/palantir/message_source/udp_source.o \
	   $(SOURCES_DIR)/palantir/udp/udp_client.o $(SOURCES_DIR)/palantir/message_destination/console_out.o $(SOURCES_DIR)/palantir/message_destination/file_destination.o $(SOURCES_DIR)/palantir/message_destination/udp_destination.o \
	   $(SOURCES_DIR)/palantir/udp/udp_server.o $(SOURCES_DIR)/palantir/messenger.o

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

leak-check:		# run: make leak-check
	valgrind ./$(TARGET)