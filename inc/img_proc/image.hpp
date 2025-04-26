#pragma once

#include <vector>
#include <cstddef>   // for size_t

#include "img_proc/rgb.hpp"

namespace img_proc {

/**
 * @brief Holds metadata about an image such as dimensions and maximum color value.
 */
struct ImageDetail {
    size_t max_val_;
    size_t height_;
    size_t width_;
};

/**
 * @brief Represents a 2D image composed of RGB pixels.
 * 
 * @tparam T Unsigned integral type for pixel channels.
 */
template<typename T>
class Image {
public:
    /**
     * @brief Default constructor. Creates an empty image (0x0, max_val = 255).
     */
    Image() = default;

    /**
     * @brief Constructs an image with initialized pixel data.
     * 
     * @param vec Pixel data to load (moved into the image).
     * @param height Height of the image.
     * @param width Width of the image.
     * @param max_val Maximum pixel value (e.g., 255 for 8-bit images).
     */
    explicit Image(std::vector<RGB<T>>&& vec, size_t height, size_t width, size_t max_val);

    /**
     * @brief Constructs an empty image with specified dimensions.
     * 
     * @param height Height of the image.
     * @param width Width of the image.
     * @param max_val Maximum pixel value.
     */
    explicit Image(size_t height, size_t width, size_t max_val);

    ~Image() = default;

    Image(Image const& other);
    Image(Image&& other) noexcept;

    Image& operator=(Image const& other);
    Image& operator=(Image&& other) noexcept;

    /**
     * @brief Loads bulk pixel data and metadata into the image.
     * 
     * @param vec Pixel data (moved).
     * @param details Image dimensions and maximum color value.
     */
    void load_bulk(std::vector<RGB<T>>&& vec, ImageDetail const& details);

    /**
     * @brief Provides mutable access to a pixel at a given linear index.
     * 
     * @param index Index in the flat pixel array.
     * @return Reference to the RGB pixel.
     */
    RGB<T>& operator[](size_t index);

    /**
     * @brief Provides read-only access to a pixel at a given linear index.
     * 
     * @param index Index in the flat pixel array.
     * @return Constant reference to the RGB pixel.
     */
    RGB<T> const& operator[](size_t index) const;

    /**
     * @brief Compares two images for equality (dimensions, max value, pixel content).
     * 
     * @param other Image to compare with.
     * @return true if the images are identical, false otherwise.
     */
    bool operator==(const Image<T>& other) const noexcept;

    /**
     * @brief Resizes the image dimensions and pixel array.
     * 
     * @param new_height New height.
     * @param new_width New width.
     * @param new_max_val New maximum color value.
     * 
     * @note Previous pixel data is discarded or preserved depending on the new size.
     */
    void resize(size_t new_height, size_t new_width, size_t new_max_val);

    /**
     * @brief Returns the number of pixels (width × height).
     */
    size_t size() const noexcept;

    /**
     * @brief Prints the entire image to std::cout (as a grid of RGB values).
     */
    void print_image() const;

    /**
     * @brief Returns the image height.
     */
    size_t height() const noexcept;

    /**
     * @brief Returns the image width.
     */
    size_t width() const noexcept;

    /**
     * @brief Returns the image maximum color value.
     */
    size_t max_val() const noexcept;

    /**
     * @brief Calculates the 1D array index from 2D coordinates.
     * 
     * @param row Row index (0-based).
     * @param column Column index (0-based).
     * @return Linearized index for the pixel array.
     */
    size_t at_index(size_t row, size_t column) const noexcept;

private:
    size_t height_{0};
    size_t width_{0};
    size_t max_val_{255};
    std::vector<RGB<T>> pixels_;
};

} // namespace img_proc

#include "img_proc/image.inl"
