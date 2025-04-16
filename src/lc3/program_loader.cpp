#include <utility> // std::move

#include "lc3/program_loader.hpp"
#include "lc3/consts_and_sizes.hpp"

namespace lc3 {

namespace program_loader {

void program_loader(const std::string& file_path, Memory& memory)
{
    Loader loader;
    std::vector<Word> program = loader.load(file_path);
    memory.load_dense(std::move(program), loader.get_start_address());
}

} // namespace program_loader

} // namespace lc3
