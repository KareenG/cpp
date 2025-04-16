#include <fstream>
#include <filesystem>  // Add this include

#include "lc3/loader.hpp"
#include "lc3/utility.hpp"
#include "lc3/lc3_exceptions.hpp"  // For FileOpenException

namespace lc3 {

std::vector<Word> Loader::load(std::string const& file_path)
{
    std::ifstream fs{file_path, std::ios::binary};
    if (!fs) {
        throw FileOpenException(file_path);
    }

    // Read origin address
    Address origin;
    fs.read(reinterpret_cast<char*>(&origin), sizeof(origin));
    origin = from_big_endian(origin);
    start_address_ = origin;

    // Use filesystem to get file size and compute number of instructions
    std::uintmax_t file_size = std::filesystem::file_size(file_path);
    std::size_t instr_count = static_cast<std::size_t>((file_size - sizeof(Word)) / sizeof(Word));

    std::vector<Word> program;
    program.reserve(instr_count);

    Word instruction_word;
    while (fs.read(reinterpret_cast<char*>(&instruction_word), sizeof(instruction_word))) {
        program.push_back(from_big_endian(instruction_word));
    }

    return program;
}

Address Loader::get_start_address() const noexcept
{
    return start_address_;
}

} // namespace lc3

