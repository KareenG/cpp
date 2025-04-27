#pragma once

#include <string>
#include <vector>
#include <thread>

#include "img_proc/image_proc_interface.hpp"
#include "img_proc/thread_wrkr.hpp"
#include "img_proc/image.hpp"

namespace img_proc {

template<typename T>
class NullTransformer : public ImageTransformer<T> {
public:
    Image<T> transform_image(Image<T> const& original_image, size_t threads = std::thread::hardware_concurrency()) override;
};

template<typename T>
class ColorReduction : public ImageTransformer<T> {
public:
    explicit ColorReduction(size_t channel_levels = 2);
    Image<T> transform_to_bw(Image<T> const& original_image) const;
    Image<T> transform_image(Image<T> const& original_image, size_t threads = std::thread::hardware_concurrency()) override;

private:
    size_t levels_;
};

template<typename T>
class Pixelator : public ImageTransformer<T> {
public:
    explicit Pixelator(size_t block_size);
    Image<T> transform_image(Image<T> const& original_image, size_t threads = std::thread::hardware_concurrency()) override;

private:
    // std::vector<std::vector<RGB<T>>> compute_relevant_block_averages(Image<T> const& image, size_t start_row, size_t end_row) const;
    // RGB<T> compute_block_average(Image<T> const& image, size_t block_row, size_t block_col) const;
    std::vector<std::vector<RGB<T>>> precompute_block_averages(Image<T> const& image) const;

private:
    size_t block_size_;
};

template<typename T>
class GaussianBlur : public ImageTransformer<T> {
public:
    explicit GaussianBlur(size_t kernel_size = 5, double sigma = 1.0);
    Image<T> transform_image(Image<T> const& original_image, size_t threads = std::thread::hardware_concurrency()) override;

private:
    std::vector<std::vector<double>> generate_gaussian_kernel(int size, double sigma) const;
    RGB<T> apply_kernel_to_pixel(Image<T> const& image, std::vector<std::vector<double>> const& kernel, int y, int x, int half_k) const;

private:
    size_t kernel_size_;
    double sigma_;
};

} // namespace img_proc

#include "img_proc/image_proc.inl"