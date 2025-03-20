#pragma once

#include <functional>  // Include for std::less

namespace utils {

template<typename T, typename LessComp = std::less<T>>
T clamp(T const& low, T const& high, T const& val, LessComp less = LessComp()) 
{
    if(less(val, low)) {
        return low;
    }
    else if (less(high, val)) {
        return high;
    }
    return val;
}

}   // namespace utils