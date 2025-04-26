#pragma once

#include <iomanip>    // For std::setw

#include "img_proc/rgb.hpp"

namespace img_proc {

template<typename T>
RGB<T>::RGB(T red, T green, T blue)
: r{red}, g{green}, b{blue}
{
}

template<typename T>
RGB<T>::RGB(T c)
: RGB(c, c, c)
{
}

template<typename T>
T RGB<T>::to_intensity() const noexcept
{
    return static_cast<T>(0.299 * r + 0.587 * g + 0.114 * b);
}

template<typename T>
RGB<T> RGB<T>::white() noexcept
{
    return RGB(255, 255, 255);
}

template<typename T>
RGB<T> RGB<T>::black() noexcept
{
    return RGB(0, 0, 0);
}

template<typename T>
void RGB<T>::print(std::ostream& os) const
{
    os << std::left
       << std::setw(3) << static_cast<int>(r) << " "
       << std::setw(3) << static_cast<int>(g) << " "
       << std::setw(3) << static_cast<int>(b) << " ";
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const RGB<T>& rgb)
{
    rgb.print(os);
    return os;
}

template<typename T>
bool RGB<T>::operator==(const RGB<T>& other) const noexcept
{
    return (r == other.r) && (g == other.g) && (b == other.b);
}

} // namespace img_proc
