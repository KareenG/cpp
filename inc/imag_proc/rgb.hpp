#pragma once

#include <cstdint>

/**
 * @brief Represents an RGB pixel with 8-bit channels.
 */
struct RGB {
    uint8_t r, g, b;

    RGB() = default;
    RGB(uint8_t red, uint8_t green, uint8_t blue);

    /**
     * @brief Converts the RGB pixel to a grayscale intensity (0–255).
     * @return Approximate luminance.
     */
    uint8_t to_intensity() const noexcept;

    /**
     * @brief Returns a white pixel (255, 255, 255).
     */
    static RGB white() noexcept;

    /**
     * @brief Returns a black pixel (0, 0, 0).
     */
    static RGB black() noexcept;
};

#include "imag_proc/rgb.inl"