#include <utility>   // for std::move

#include "lc3/program_loader.hpp"

namespace lc3 {

ProgramLoader::ProgramLoader(std::string const& file_path, Memory& memory)
: loader_{}
, memory_{memory}
{
    std::vector<uint16_t> program = loader_.load(file_path);
    memory_.load_dense(std::move(program), loader_.get_start_address());
}

} // namespace lc3
