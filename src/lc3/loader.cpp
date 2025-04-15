#include <fstream>
#include <cassert>
#include <netinet/in.h> // for ntohs

#include "lc3/loader.hpp"

namespace lc3 {

std::vector<uint16_t> Loader::load(std::string const& file_path)
{
    std::ifstream fs{file_path, std::ios::binary};
    
    assert(fs && "Failed to open binary file");

    uint16_t origin;
    fs.read(reinterpret_cast<char*>(&origin), sizeof(origin));
    origin = ntohs(origin);  // Convert from big endian

    start_address_ = origin;

    std::vector<uint16_t> program;
    uint16_t instruction_word;

    while (fs.read(reinterpret_cast<char*>(&instruction_word), sizeof(instruction_word))) {
        program.push_back(ntohs(instruction_word)); // Store in host byte order
    }

    return program;
}

uint16_t Loader::get_start_address() const noexcept
{
    return start_address_;
}

} // namespace lc3
