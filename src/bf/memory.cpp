#include "bf/memory.hpp"
#include <iostream>

namespace bf {

Memory::Memory(size_t size)
: tape_(size, 0)
, pointer_{0}
{
}

CellType Memory::read() 
{
    return (tape_[pointer_]);
}

void Memory::write(CellType c) 
{
    tape_[pointer_] = c;
}

void Memory::move_left() 
{
    if (pointer_ > 0) {
        --pointer_;
    }
    else {
        pointer_ = tape_.size() - 1;
    }
}

void Memory::move_right() 
{
    if (pointer_ < tape_.size() - 1) {
        ++pointer_;
    }
    else {
        pointer_ = 0;
    }
}

#ifdef BF_DEBUG
CellType Memory::operator[](Index index) const 
{
    return tape_[index];
}
#endif

// CellType Memory::operator[](Index index) const 
// {
//     return tape_[index];
// }

} // namespace bf
