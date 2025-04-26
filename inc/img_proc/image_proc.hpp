#pragma once

#include <string>
#include <vector>

#include "img_proc/thread_wrkr.hpp"
#include "img_proc/image.hpp"

namespace img_proc {
    
/**
 * @brief Interface for image transformation strategies (strategy pattern).
 */
template<typename T>
class ImageTransformer {
public:
    virtual ~ImageTransformer() = default;

    /**
     * @brief Applies transformation to the given image.
     * @param original_image The source image to read from (const).
     * @param image_transformed The image to write the transformation result into.
     * @param threads Number of threads to use.
     */
    virtual void transform_image(Image<T> const& original_image, Image<T>& image_transformed, size_t threads = 1) const = 0;
};

template<typename T>
class NullTransformer : public ImageTransformer<T> {
public:
    void transform_image(Image<T> const& original_image, Image<T>& image_transformed, size_t threads = 1) const override;
};

template<typename T>
class ColorReduction : public ImageTransformer<T> {
public:
    explicit ColorReduction(size_t channel_levels = 2);
    void transform_to_bw(Image<T> const& original_image, Image<T>& image_transformed) const;
    void transform_image(Image<T> const& original_image, Image<T>& image_transformed, size_t threads = 1) const override;

private:
    size_t levels_;
};

template<typename T>
class Pixelator : public ImageTransformer<T> {
public:
    explicit Pixelator(size_t block_size);
    void transform_image(Image<T> const& original_image, Image<T>& image_transformed, size_t threads = 1) const override;

private:
    std::vector<std::vector<RGB<T>>> precompute_block_averages(Image<T> const& image) const;

private:
    size_t block_size_;
};

template<typename T>
class GaussianBlur : public ImageTransformer<T> {
public:
    explicit GaussianBlur(size_t kernel_size = 5, double sigma = 1.0);
    void transform_image(Image<T> const& original_image, Image<T>& image_transformed, size_t threads = 1) const override;

private:
    std::vector<std::vector<double>> generate_gaussian_kernel(int size, double sigma) const;
    RGB<T> apply_kernel_to_pixel(Image<T> const& image, std::vector<std::vector<double>> const& kernel, int y, int x, int half_k) const;

private:
    size_t kernel_size_;
    double sigma_;
};

} // namespace img_proc

#include "img_proc/image_proc.inl"