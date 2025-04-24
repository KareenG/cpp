#pragma once

#include "imag_proc/rgb.hpp"

RGB::RGB(uint8_t red, uint8_t green, uint8_t blue)
: r(red), g(green), b(blue) {}

// These are coefficients that come from the definition of the ITU-R BT.601 standard.
// An old digital television standard that remains in use because of its accuracy and convenience.
uint8_t RGB::to_intensity() const noexcept
{
    return static_cast<uint8_t>(0.299 * r + 0.587 * g + 0.114 * b);
}

RGB RGB::white() noexcept {
    return RGB(255, 255, 255);
}

RGB RGB::black() noexcept {
    return RGB(0, 0, 0);
}
