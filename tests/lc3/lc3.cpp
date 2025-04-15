#include <iostream>
#include <string>

#include "lc3/memory.hpp"
#include "lc3/console.hpp"
#include "lc3/cpu.hpp"
#include "lc3/program_loader.hpp"

int main(int argc, char* argv[])
{
    if (argc != 2) {
        std::cerr << "Usage: lc3 <program_file.bin>\n";
        return -1;
    }

    const std::string file_path = argv[1];

    lc3::Memory memory{};
    lc3::Console console{};
    lc3::ProgramLoader loader(file_path, memory);
    lc3::CPU cpu(memory, console);

    cpu.run();

    return 0;
}
