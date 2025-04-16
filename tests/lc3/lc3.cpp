#include <iostream>
#include <string>

#include "lc3/memory.hpp"
#include "lc3/console.hpp"
#include "lc3/cpu.hpp"
#include "lc3/program_loader.hpp"
#include "lc3/lc3_exceptions.hpp"  // For LC-3-specific exceptions
#include "lc3/terminal_io.hpp"

int main(int argc, char* argv[])
{
    if (argc != 2) {
        std::cerr << "Usage: lc3 <program_file.bin>\n";
        return EXIT_FAILURE;
    }

    lc3::TerminalIO terminal_guard;  // Ensures terminal is restored on exit

    const std::string file_path = argv[1];

    try {
        lc3::Memory memory;
        lc3::Console console;
        lc3::program_loader::program_loader(file_path, memory);
        lc3::CPU cpu(memory, console);
        cpu.run();

    } catch (const lc3::FileOpenException& e) {
        std::cerr << "[File Error] " << e.what() << '\n';
        return EXIT_FAILURE;
    } catch (const lc3::MemoryBoundsException& e) {
        std::cerr << "[Memory Error] " << e.what() << '\n';
        return EXIT_FAILURE;
    } catch (const lc3::InvalidOpcodeException& e) {
        std::cerr << "[Opcode Error] " << e.what() << '\n';
        return EXIT_FAILURE;
    } catch (...) {
        std::cerr << "[Unknown Error] An unexpected error occurred.\n";
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
