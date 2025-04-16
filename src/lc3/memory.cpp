#include "lc3/memory.hpp"
#include "lc3/lc3_exceptions.hpp"  // For MemoryBoundsException

namespace lc3
{

Memory::Memory(Address start)
: memory_(MemorySize, 0)
, start_{start}
{
}

void Memory::load_dense(std::vector<Word>&& data, Address start_addr)
{
    if (data.size() > MemorySize  - start_addr) {
        throw MemoryBoundsException(MemorySize);
    }

    for (size_t i = 0; i < data.size(); ++i) {
        memory_[start_addr + i] = data[i];
    }
    start_ = start_addr;
}

Address Memory::get_program_start() const noexcept
{
    return start_;
}

Word Memory::read(uint16_t address) const noexcept
{
    return memory_[address];
}

void Memory::write(Address address, Word value) noexcept
{
    memory_[address] = value;
}

} // namespace lc3
