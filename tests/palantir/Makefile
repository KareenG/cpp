CXX=g++
CXXFLAGS=-pedantic -Wall -Werror -Wextra -g3 -std=c++17
CPPFLAGS=-I$(INCLUDES_DIR)

INCLUDES_DIR=../../inc
SOURCES_DIR=../../src

# List of objects
OBJS = $(SOURCES_DIR)/palantir/encryption/atbash.o \
       $(SOURCES_DIR)/palantir/encryption/caesar.o \
       $(SOURCES_DIR)/palantir/encryption/rot13.o \
       $(SOURCES_DIR)/palantir/encryption/vigenere.o \
       $(SOURCES_DIR)/palantir/encryption/null_encryption.o \
       $(SOURCES_DIR)/palantir/message_source/console_in.o \
       $(SOURCES_DIR)/palantir/message_source/file_source.o \
       $(SOURCES_DIR)/palantir/message_source/udp_source.o \
       $(SOURCES_DIR)/palantir/message_source/tcp_source.o \
       $(SOURCES_DIR)/net/udp/udp_client.o \
       $(SOURCES_DIR)/net/udp/udp_server.o \
       $(SOURCES_DIR)/palantir/message_destination/console_out.o \
       $(SOURCES_DIR)/palantir/message_destination/file_destination.o \
       $(SOURCES_DIR)/palantir/message_destination/udp_destination.o \
       $(SOURCES_DIR)/palantir/message_destination/tcp_destination.o \
       $(SOURCES_DIR)/net/tcp/tcp_client.o \
       $(SOURCES_DIR)/net/tcp/tcp_server.o \
       $(SOURCES_DIR)/palantir/messenger.o \
       $(SOURCES_DIR)/palantir/encryption/key_base_encryptor.o \
       $(SOURCES_DIR)/palantir/encryption/rotate.o \
       $(SOURCES_DIR)/palantir/encryption/xor.o

RUN_PALANTIR_OBJS = $(OBJS) $(SOURCES_DIR)/palantir/command_line_args.o

# Executables
RUN_PALANTIR = $(SOURCES_DIR)/palantir/run_palantir
UTEST=utest
UDP_SOURCE_MAIN=udp_source_main
UDP_DESTINATION_MAIN=udp_destination_main


all: $(UTEST) $(UDP_SOURCE_MAIN) $(UDP_DESTINATION_MAIN) $(RUN_PALANTIR)

$(RUN_PALANTIR) : CPPFLAGS += -DNDEBUG
$(RUN_PALANTIR) : $(RUN_PALANTIR_OBJS)

$(UTEST) : CPPFLAGS += -DBF_DEBUG
$(UTEST) : $(OBJS)

$(UDP_SOURCE_MAIN) : CPPFLAGS += -DBF_DEBUG
$(UDP_SOURCE_MAIN) : $(OBJS)

$(UDP_DESTINATION_MAIN) : CPPFLAGS += -DBF_DEBUG
$(UDP_DESTINATION_MAIN) : $(OBJS)

clean:
	$(RM) $(UTEST) $(OBJS) $(RUN_PALANTIR) $(RUN_PALANTIR_OBJS)

check: all
	./utest

recheck: clean check

leak-check:
	valgrind --leak-check=full ./utest

.PHONY: all clean check recheck leak-check
