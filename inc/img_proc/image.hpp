#pragma once

#include <vector>
#include <cstddef>  
#include <string>
#include <istream>
#include <ostream>
#include <type_traits> 

#include "img_proc/rgb.hpp"

namespace img_proc {
namespace image {

/**
 * @brief Represents a 2D image composed of RGB pixels.
 * 
 * @tparam T Unsigned integral type for pixel channels.
 */
template<typename T>
class Image {
    static_assert(!std::is_same_v<T, uint8_t>, "T must not be uint8_t");
    static_assert(!std::is_same_v<T, char>, "T must not be char");

public:
    /**
     * @brief Default constructor. Creates an empty image (0x0, max_color = 255).
     */
    Image() = default;

    /**
     * @brief Constructs an image with initialized pixel data.
     * 
     * @param vec Pixel data to load (moved into the image).
     * @param height Height of the image.
     * @param width Width of the image.
     * @param max_color Maximum pixel value (e.g., 255 for 8-bit images).
     */
    Image(std::vector<RGB<T>>&& vec, size_t height, size_t width, size_t max_color);

    /**
     * @brief Constructs an empty image with specified dimensions.
     * 
     * @param height Height of the image.
     * @param width Width of the image.
     * @param max_color Maximum pixel value.
     */
    Image(size_t height, size_t width, size_t max_color);

    /**
     * @brief Provides mutable access to a pixel at a given linear index.
     */
    RGB<T>& operator[](size_t index);

    /**
     * @brief Provides read-only access to a pixel at a given linear index.
     */
    const RGB<T>& operator[](size_t index) const;

    /**
     * @brief Access a pixel at given (row, column) with bounds checking.
     */
    RGB<T>& operator()(size_t row, size_t column);

    /**
     * @brief Read-only access to a pixel at (row, column) with bounds checking.
     */
    RGB<T> operator()(size_t row, size_t column) const;

    /**
     * @brief Compares two images for equality.
     */
    bool operator==(const Image<T>& other) const noexcept;

    /**
     * @brief Resizes the image dimensions and pixel array.
     */
    void resize(size_t new_height, size_t new_width, size_t new_max_color);

    /**
     * @brief Returns the number of pixels (width × height).
     */
    size_t size() const noexcept;

    /**
     * @brief Prints the entire image to std::cout.
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
     * @brief Returns the maximum color value.
     */
    size_t max_color() const noexcept;

private:
    size_t height_{0};
    size_t width_{0};
    size_t max_color_{255};
    std::vector<RGB<T>> pixels_;
};

/**
 * @brief Loads an image from a file path.
 * @throws FileOpenException if file cannot be opened.
 */
template<typename T>
Image<T> image_loader(const std::string& file_path);

/**
 * @brief Loads an image from an input stream.
 * @throws FileASCIIException or InputStreamException if invalid.
 */
template<typename T>
Image<T> image_loader(std::istream& is);

/**
 * @brief Saves an image to a file path.
 * @throws FileOpenException or OutputStreamException if invalid.
 */
template<typename T>
void image_saver(const std::string& file_path, Image<T>& image);

/**
 * @brief Saves an image to an output stream.
 * @throws OutputStreamException if invalid.
 */
template<typename T>
void image_saver(std::ostream& os, Image<T>& image);

} // namespace image
} // namespace img_proc

#include "img_proc/image.inl"























// #pragma once

// #include <vector>
// #include <cstddef>   // for size_t
// #include <string>
// #include <istream>
// #include <ostream>

// #include "img_proc/rgb.hpp"

// namespace img_proc {

// // /**
// //  * @brief Holds metadata about an image such as dimensions and maximum color value.
// //  */
// // struct ImageDetail {
// //     size_t max_color_;
// //     size_t height_;
// //     size_t width_;
// // };

// namespace image {

// /**
//  * @brief Represents a 2D image composed of RGB pixels.
//  * 
//  * @tparam T Unsigned integral type for pixel channels.
//  */
// template<typename T>
// class Image {
//     static_assert(!std::is_same_v<T, uint8_t>, "T must not be uint8_t");
//     static_assert(!std::is_same_v<T, char>, "T must not be char");
// public:
//     /**
//      * @brief Default constructor. Creates an empty image (0x0, max_color = 255).
//      */
//     Image() = default;

//     /**
//      * @brief Constructs an image with initialized pixel data.
//      * 
//      * @param vec Pixel data to load (moved into the image).
//      * @param height Height of the image.
//      * @param width Width of the image.
//      * @param max_color Maximum pixel value (e.g., 255 for 8-bit images).
//      */
//     explicit Image(std::vector<RGB<T>>&& vec, size_t height, size_t width, size_t max_color);

//     /**
//      * @brief Constructs an empty image with specified dimensions.
//      * 
//      * @param height Height of the image.
//      * @param width Width of the image.
//      * @param max_color Maximum pixel value.
//      */
//     explicit Image(size_t height, size_t width, size_t max_color);

//     // ~Image() = default;

//     // Image(Image const& other) = default;
//     // Image(Image&& other) noexcept = default;

//     // Image& operator=(Image const& other) = default;
//     // Image& operator=(Image&& other) noexcept = default;

//     /**
//      * @brief Loads bulk pixel data and metadata into the image.
//      * 
//      * @param vec Pixel data (moved).
//      * @param details Image dimensions and maximum color value.
//      */
//     //void load_bulk(std::vector<RGB<T>>&& vec, ImageDetail const& details);

//     /**
//      * @brief Provides mutable access to a pixel at a given linear index.
//      * 
//      * @param index Index in the flat pixel array.
//      * @return Reference to the RGB pixel.
//      */
//     RGB<T>& operator[](size_t index);

//     /**
//      * @brief Provides read-only access to a pixel at a given linear index.
//      * 
//      * @param index Index in the flat pixel array.
//      * @return Constant reference to the RGB pixel.
//      */
//     RGB<T> const& operator[](size_t index) const;

//     /**
//      * @brief Compares two images for equality (dimensions, max value, pixel content).
//      * 
//      * @param other Image to compare with.
//      * @return true if the images are identical, false otherwise.
//      */
//     bool operator==(const Image<T>& other) const noexcept;

//     /**
//      * @brief Resizes the image dimensions and pixel array.
//      * 
//      * @param new_height New height.
//      * @param new_width New width.
//      * @param new_max_color New maximum color value.
//      * 
//      * @note Previous pixel data is discarded or preserved depending on the new size.
//      */
//     void resize(size_t new_height, size_t new_width, size_t new_max_color);

//     /**
//      * @brief Returns the number of pixels (width × height).
//      */
//     size_t size() const noexcept;

//     /**
//      * @brief Prints the entire image to std::cout (as a grid of RGB values).
//      */
//     void print_image() const;

//     /**
//      * @brief Returns the image height.
//      */
//     size_t height() const noexcept;

//     /**
//      * @brief Returns the image width.
//      */
//     size_t width() const noexcept;

//     /**
//      * @brief Returns the image maximum color value.
//      */
//     size_t max_color() const noexcept;

//     /**
//      * @brief Calculates the 1D array index from 2D coordinates.
//      * 
//      * @param row Row index (0-based).
//      * @param column Column index (0-based).
//      * @return Linearized index for the pixel array.
//      * @throw If out of bounds.
//      */
//     //size_t at_index(size_t row, size_t column) const;

//     RGB<T>& operator()(size_t row, size_t column);
//     RGB<T> operator()(size_t row, size_t column) const;


//     // void load(std::string const& file_path);
//     // void load(std::istream& is);

//     // void save(std::string const& file_path);
//     // void save(std::ostream& os);

// private:
//     size_t height_{0};
//     size_t width_{0};
//     size_t max_color_{255};
//     std::vector<RGB<T>> pixels_;
// };

// /**
//  * @brief Loads an image from a file path.
//  * @throws FileOpenException if the file cannot be opened.
//  * @throws FileASCIIException if the file format is not P3.
//  * @throws InputStreamException if the file content is invalid.
//  */
// template<typename T>
// Image<T> image_loader(std::string const& file_path);

// /**
//  * @brief Loads an image from an input stream.
//  * @throws FileASCIIException if the stream does not contain a valid P3 PPM image.
//  * @throws InputStreamException if the stream is invalid.
//  */
// template<typename T>
// Image<T> image_loader(std::istream& is);

// /**
//  * @brief Saves an image to a file path.
//  * @throws FileOpenException if the file cannot be opened for writing.
//  * @throws OutputStreamException if writing to the file fails.
//  */
// template<typename T>
// void image_saver(std::string const& file_path, Image<T>& image);

// /**
//  * @brief Saves an image to an output stream.
//  * @throws OutputStreamException if the output stream is invalid.
//  */
// template<typename T>
// void image_saver(std::ostream& os, Image<T>& image);

// } // namespace image

// } // namespace img_proc

// #include "img_proc/image.inl"
