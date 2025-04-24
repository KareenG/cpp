#pragma once

#include <string>
#include <vector>

#include "imag_proc/thread_wrkr.hpp"

/**
 * @brief Templated image processor for basic operations.
 * 
 * @tparam T Pixel type, e.g., RGB.
 */
template<typename T>
class ImageProcessor {
public:
    /**
     * @brief Loads an image from a Netpbm file (PPM binary).
     * @param file_path Path to the image file.
     */
    explicit ImageProcessor(const std::string& file_path);

    /**
     * @brief Saves the processed image to a file.
     */
    void save(const std::string& file_path) const;

    /**
     * @brief Converts grayscale intensity to black/white.
     * @param threads Number of threads to use.
     */
    void reduce_colors(std::size_t threads);

    /**
     * @brief Pixelates the image using average blocks of size block_size x block_size.
     * @param block_size Size of the square block.
     * @param threads Number of threads to use.
     */
    void pixelate(std::size_t block_size, std::size_t threads);

    /**
     * @brief Applies blur (box filter) using a 3x3 kernel.
     * @param threads Number of threads to use.
     */
    void blur(std::size_t threads);

private:
    std::size_t width_;
    std::size_t height_;
    std::vector<T> pixels_;

    void load_netpbm(const std::string& file_path);
    void save_netpbm(const std::string& file_path) const;
};

#include "image_proc.inl"