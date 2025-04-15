#include <cassert>

#include "lc3/memory.hpp"

namespace lc3
{

Memory::Memory(uint16_t start)
: memory_(MEMORY_SIZE, 0)
, start_{start}
{
}

void Memory::load_dense(std::vector<uint16_t>&& data, uint16_t start_addr)
{
    assert(data.size() <= MEMORY_SIZE - start_addr && "Program too large to fit in memory");
    for (size_t i = 0; i < data.size(); ++i) {
        memory_[start_addr + i] = data[i];
    }
    start_ = start_addr;
}

uint16_t Memory::get_program_start() const noexcept
{
    return start_;
}

uint16_t Memory::read(uint16_t address) const noexcept
{
    return memory_[address];
}

void Memory::write(uint16_t address, uint16_t value) noexcept
{
    memory_[address] = value;
}

} // namespace lc3
