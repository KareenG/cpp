#pragma once

#include <cstdint>
#include <thread>

#include "img_proc/image.hpp"

namespace img_proc {
    
using image::Image;    
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
    virtual Image<T> transform_image(Image<T> const& original_image, size_t threads = std::thread::hardware_concurrency()) = 0;
};

} // namespace img_proc