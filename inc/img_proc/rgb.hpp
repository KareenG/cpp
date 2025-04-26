#pragma once

#include <cstdint>     // For uint8_t, uint16_t, etc.
#include <ostream>     // For std::ostream
#include <type_traits> // For static_assert on T

namespace img_proc {

/**
 * @brief Represents an RGB pixel with channels of type T.
 * 
 * @tparam T Must be an unsigned integral type (e.g., uint8_t, uint16_t).
 * 
 * @note Compile-time check ensures T is an unsigned integral type.
 */
template<typename T>
struct RGB {
    static_assert(std::is_integral<T>::value && std::is_unsigned<T>::value,
        "RGB<T> must use an unsigned integral type.");

    T r;
    T g;
    T b;

    /**
     * @brief Constructs an RGB pixel with all channels set to the same value.
     * @param c The value for R, G, and B.
     */
    explicit RGB(T c);

    /**
     * @brief Constructs an RGB pixel with specified red, green, and blue values.
     * @param red Red channel value.
     * @param green Green channel value.
     * @param blue Blue channel value.
     */
    RGB(T red = 0, T green = 0, T blue = 0);

    /**
     * @brief Equality operator.
     * @param other Another RGB pixel to compare against.
     * @return True if all components are equal.
     */
    bool operator==(const RGB<T>& other) const noexcept;

    /**
     * @brief Converts the RGB pixel to a grayscale intensity (0–255 scale).
     * @return The approximate luminance.
     * @note used to reduce colors to black and white.
     */
    T to_intensity() const noexcept;

    /**
     * @brief Prints the RGB values to a given output stream.
     * @param os Output stream.
     */
    void print(std::ostream& os) const;

    /**
     * @brief Returns a white pixel (all channels at maximum value 255).
     * @return White RGB pixel.
     */
    static RGB white() noexcept;

    /**
     * @brief Returns a black pixel (all channels at zero).
     * @return Black RGB pixel.
     */
    static RGB black() noexcept;
};

/**
 * @brief Stream insertion operator for RGB.
 * @param os Output stream.
 * @param rgb RGB pixel to print.
 * @return Reference to the output stream.
 */
template<typename T>
std::ostream& operator<<(std::ostream& os, const RGB<T>& rgb);

} // namespace img_proc

#include "img_proc/rgb.inl"
