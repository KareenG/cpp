#pragma once

#include <fstream>
#include <stdexcept>
#include <algorithm>

#include "imag_proc/image_proc.hpp"
#include "imag_proc/rgb.hpp"

template<typename T>
ImageProcessor<T>::ImageProcessor(const std::string& file_path)
{
    load_netpbm(file_path);
}

template<typename T>
void ImageProcessor<T>::save(const std::string& file_path) const
{
    save_netpbm(file_path);
}

template<>
void ImageProcessor<RGB>::load_netpbm(const std::string& file_path)
{
    std::ifstream in(file_path, std::ios::binary);
    if (!in) {
        throw std::runtime_error("Failed to open file");
    }

    std::string header;
    in >> header;

    // P6 is a header for PPM binary files according to the Netpbm standard.
    if (header != "P6") {
        throw std::runtime_error("Only P6 PPM is supported");
    }

    in >> width_ >> height_;
    int max_val;
    in >> max_val;
    in.ignore(); // skip newline

    pixels_.resize(width_ * height_);
    in.read(reinterpret_cast<char*>(pixels_.data()), width_ * height_ * 3); // sizeof(RGB) = 3 * uint8_t = 3 bytes
}

template<>
void ImageProcessor<RGB>::save_netpbm(const std::string& file_path) const
{
    std::ofstream out(file_path, std::ios::binary);
    if (!out) {
        throw std::runtime_error("Failed to open output file");
    }

    out << "P6\n" << width_ << ' ' << height_ << "\n255\n";
    out.write(reinterpret_cast<const char*>(pixels_.data()), width_ * height_ * 3);
}

template<>
void ImageProcessor<RGB>::reduce_colors(std::size_t threads)
{
    ThreadWorker worker(threads);

    worker.run(height_, [this](std::size_t start, std::size_t end) {
        for (std::size_t y = start; y < end; ++y) {
            for (std::size_t x = 0; x < width_; ++x) {
                RGB& px = pixels_[y * width_ + x];

            }
        }
    });
}





