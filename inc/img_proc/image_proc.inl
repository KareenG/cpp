#pragma once

#include <fstream>
#include <stdexcept>
#include <algorithm>

#include <unordered_map>
#include <tuple>
#include <cmath>
#include <cstdint>

#include "img_proc/image_proc.hpp"
#include "img_proc/rgb.hpp"
#include "img_proc/thread_wrkr.hpp"
#include "img_proc/img_proc_exceptions.hpp"

namespace img_proc {

template<typename T>
Image<T> NullTransformer<T>::transform_image(Image<T> const& original_image, size_t threads)
{
    Image<T> image_transformed = Image<T>{original_image.height(), original_image.width(), original_image.max_color()};

    ThreadWorker worker(threads);
    worker.run(original_image.height(),
        [&original_image, &image_transformed](std::size_t start_row, std::size_t end_row) {
            for (size_t row = start_row; row < end_row; ++row) {
                for (size_t col = 0; col < original_image.width(); ++col) {
                    image_transformed(row, col) = original_image(row, col);
                }
            }
        }
    );

    return image_transformed;
}


template<typename T>
ColorReduction<T>::ColorReduction(size_t channel_levels)
: levels_{channel_levels}
{
}

template<typename T>
using Quantizer = std::function<T(T)>;

template<typename T>
static std::array<Quantizer<T>, 3> make_quantizers(std::vector<T> const& bins) {
    return {
        [&bins](T r) {
            return *std::min_element(bins.begin(), bins.end(), [r](T a, T b) {
                return std::abs(a - r) < std::abs(b - r);
            });
        },
        [&bins](T g) {
            return *std::min_element(bins.begin(), bins.end(), [g](T a, T b) {
                return std::abs(a - g) < std::abs(b - g);
            });
        },
        [&bins](T b) {
            return *std::min_element(bins.begin(), bins.end(), [b](T a, T b2) {
                return std::abs(a - b) < std::abs(b2 - b);
            });
        }
    };
}

template<typename T>
Image<T> ColorReduction<T>::transform_to_bw(Image<T> const& original_image) const {
    Image<T> image_transformed = Image<T>{original_image.height(), original_image.width(), original_image.max_color()};

    T upper_bound = original_image.max_color();
    image_transformed = original_image;
    for (size_t i = 0; i < image_transformed.size(); ++i) {
        T intensity = original_image[i].to_intensity();
        image_transformed[i] = (intensity < upper_bound / 2) ? RGB<T>::black() : RGB<T>::white();
    }
    return image_transformed;
}

template<typename T>
Image<T> ColorReduction<T>::transform_image(Image<T> const& original_image, size_t threads)
{
    // Special case for black-and-white conversion
    if(levels_ == 2) {
        return transform_to_bw(original_image);
    }

    Image<T> image_transformed = Image<T>{original_image.height(), original_image.width(), original_image.max_color()};

    std::vector<T> bins(levels_);
    size_t upper_bound = original_image.max_color();
    size_t step = upper_bound / (levels_ - 1);

    bins[0] = 0;
    for(size_t i = 1; i < levels_ - 1; ++i) {
        bins[i] = bins[i - 1] + step;
    }
    bins[levels_ - 1] = std::min(static_cast<T>(upper_bound), static_cast<T>(bins[levels_ - 2] + step));

    auto quantizers = make_quantizers<T>(bins);

    ThreadWorker worker(threads);

    worker.run(original_image.height(), 
        [&original_image, &image_transformed, &quantizers](std::size_t start, std::size_t end) {
            for(std::size_t y = start; y < end; ++y) {
                for(std::size_t x = 0; x < original_image.width(); ++x) {
                    const RGB<T>& orig_px = original_image(y, x);
                    RGB<T>& px = image_transformed(y, x);

                    px.r = quantizers[0](orig_px.r);
                    px.g = quantizers[1](orig_px.g);
                    px.b = quantizers[2](orig_px.b);
                }
            }
    });

    return image_transformed;
}

//----------------->        Option 2        DO NOT DELETE
/**
template<typename T>
void ColorReduction<T>::transform_image(Image<T> const& original_image, Image<T>& image_transformed, size_t) const {
    T upper_bound = original_image.max_color();

    // Special case for black-and-white conversion
    if (levels_ == 2) {
        transform_to_bw(original_image, image_transformed);
        return;
    }

    T step = upper_bound / static_cast<T>(levels_ - 1);  // ensure black and white bounds included

    std::vector<T> bins(levels_);
    for (size_t i = 0; i < levels_; ++i) {
        bins[i] = static_cast<T>(i * step);
    }
    bins[levels_ - 1] = upper_bound; // explicitly ensure white at end

    auto find_bin_index = [&](T value) -> size_t {
        size_t best_idx = 0;
        T min_dist = std::abs(value - bins[0]);
        for (size_t i = 1; i < bins.size(); ++i) {
            T dist = std::abs(value - bins[i]);
            if (dist < min_dist) {
                min_dist = dist;
                best_idx = i;
            }
        }
        return best_idx;
    };

    std::unordered_map<size_t, std::vector<RGB<T>>> bin_groups;

    for (size_t i = 0; i < original_image.size(); ++i) {
        const RGB<T>& px = original_image[i];
        size_t bin_idx = find_bin_index(px.to_intensity());
        bin_groups[bin_idx].push_back(px);
    }

    std::unordered_map<size_t, RGB<T>> bin_to_color;
    for (auto const& [bin_idx, group] : bin_groups) {
        uint64_t sum_r = 0, sum_g = 0, sum_b = 0;
        for (const auto& px : group) {
            sum_r += px.r;
            sum_g += px.g;
            sum_b += px.b;
        }
        size_t count = group.size();
        bin_to_color[bin_idx] = RGB<T>{
            static_cast<T>(sum_r / count),
            static_cast<T>(sum_g / count),
            static_cast<T>(sum_b / count)
        };
    }

    image_transformed = original_image;
    for (size_t i = 0; i < image_transformed.size(); ++i) {
        size_t bin_index = find_bin_index(original_image[i].to_intensity());
        image_transformed[i] = bin_to_color[bin_index];
    }
}
 */

//----------------->       End Option 2        DO NOT DELETE

template<typename T>
Pixelator<T>::Pixelator(size_t block_size)
: block_size_{block_size}
{
}

template<typename T>
Image<T> Pixelator<T>::transform_image(Image<T> const& original_image, size_t threads)
{
    Image<T> image_transformed = Image<T>{original_image.height(), original_image.width(), original_image.max_color()};

    auto block_averages = precompute_block_averages(original_image);

    ThreadWorker worker(threads);
    worker.run(original_image.height(), 
        [&original_image, &image_transformed, &block_averages, this](std::size_t start_row, std::size_t end_row) {
            for (size_t row = start_row; row < end_row; ++row) {
                for (size_t col = 0; col < original_image.width(); ++col) {
                    size_t block_row = row / block_size_;
                    size_t block_col = col / block_size_;
                    image_transformed(row, col) = block_averages[block_row][block_col];
                }
            }
        }
    );

    return image_transformed;
}

template<typename T>
std::vector<std::vector<RGB<T>>> Pixelator<T>::precompute_block_averages(Image<T> const& image) const
{
    size_t blocks_y = (image.height() + block_size_ - 1) / block_size_;
    size_t blocks_x = (image.width() + block_size_ - 1) / block_size_;

    std::vector<std::vector<RGB<T>>> block_avgs(blocks_y, std::vector<RGB<T>>(blocks_x, RGB<T>{}));

    for (size_t block_row = 0; block_row < blocks_y; ++block_row) {
        for (size_t block_col = 0; block_col < blocks_x; ++block_col) {

            RGB<uint64_t> sum{};    // Use big type to avoid overflow
            size_t pixel_count = 0;

            size_t row_start = block_row * block_size_;
            size_t row_end = std::min(row_start + block_size_, image.height());

            size_t col_start = block_col * block_size_;
            size_t col_end = std::min(col_start + block_size_, image.width());

            for (size_t row = row_start; row < row_end; ++row) {
                for (size_t col = col_start; col < col_end; ++col) {
                    RGB<T> px = image(row, col);
                    sum.r += px.r;
                    sum.g += px.g;
                    sum.b += px.b;
                    ++pixel_count;
                }
            }

            if (pixel_count > 0) {
                // Compute average
                block_avgs[block_row][block_col] = RGB<T>{
                    static_cast<T>(sum.r / pixel_count),
                    static_cast<T>(sum.g / pixel_count),
                    static_cast<T>(sum.b / pixel_count)
                };
            }
        }
    }

    return block_avgs;
}

template<typename T>
GaussianBlur<T>::GaussianBlur(size_t kernel_size, double sigma)
: kernel_size_{kernel_size}
, sigma_{sigma}
{
}

template<typename T>
Image<T> GaussianBlur<T>::transform_image(Image<T> const& original_image, size_t threads)
{
    int half_k = std::max(static_cast<int>(kernel_size_ / 2), 1);

    auto kernel = generate_gaussian_kernel(kernel_size_, sigma_);

    Image<T> image_transformed = Image<T>{original_image.height(), original_image.width(), original_image.max_color()};

    ThreadWorker worker(threads);
    worker.run(original_image.height(),
        [&, this](std::size_t start_row, std::size_t end_row) {
            for (size_t y = start_row; y < end_row; ++y) {
                for (size_t x = 0; x < original_image.width(); ++x) {
                    image_transformed(y, x) =
                        apply_kernel_to_pixel(original_image, kernel, y, x, half_k);
                }
            }
        });

    return image_transformed;
}


template<typename T>
std::vector<std::vector<double>> GaussianBlur<T>::generate_gaussian_kernel(int size, double sigma) const
{
    if (size % 2 == 0) {
        throw InvalidKernelSizeException();
    }

    std::vector<std::vector<double>> kernel(size, std::vector<double>(size));
    int half = size / 2;
    double sum = 0.0;

    for (int y = -half; y <= half; ++y) {
        for (int x = -half; x <= half; ++x) {
            double exponent = -(x * x + y * y) / (2.0 * sigma * sigma);
            double value = std::exp(exponent) / (2.0 * M_PI * sigma * sigma);
            kernel[y + half][x + half] = value;
            sum += value;
        }
    }

    // Normalize kernel
    for (auto& row : kernel) {
        for (auto& val : row) {
            val /= sum;
        }
    }

    return kernel;
}


template<typename T>
RGB<T> GaussianBlur<T>::apply_kernel_to_pixel(Image<T> const& image, std::vector<std::vector<double>> const& kernel, int y, int x, int half_k) const
{
    double r_sum = 0.0, g_sum = 0.0, b_sum = 0.0;
    int width = static_cast<int>(image.width());
    int height = static_cast<int>(image.height());

    for (int ky = -(half_k); ky <= (half_k); ++ky) {
        for (int kx = -(half_k); kx <= (half_k); ++kx) {
            int sy = std::clamp(y + ky, 0, height - 1);
            int sx = std::clamp(x + kx, 0, width - 1);

            RGB<T> px = image(static_cast<size_t>(sy), static_cast<size_t>(sx));
            double weight = kernel[ky + half_k][kx + half_k];

            r_sum += static_cast<double>(px.r) * weight;
            g_sum += static_cast<double>(px.g) * weight;
            b_sum += static_cast<double>(px.b) * weight;
        }
    }
    double upper_bound = static_cast<double>(image.max_color());
    return RGB<T>{
        static_cast<T>(std::clamp(r_sum, 0.0, upper_bound)),//255.0
        static_cast<T>(std::clamp(g_sum, 0.0, upper_bound)),//255.0
        static_cast<T>(std::clamp(b_sum, 0.0, upper_bound)),//255.0
    };
}

} // namespace img_proc













// template<typename T>
// ImageProcessor<T>::ImageProcessor(const std::string& file_path)
// {
//     load_netpbm(file_path);
// }

// template<typename T>
// void ImageProcessor<T>::save(const std::string& file_path) const
// {
//     save_netpbm(file_path);
// }

// template<>
// void ImageProcessor<RGB>::reduce_colors(std::size_t threads)
// {
//     ThreadWorker worker(threads);

//     worker.run(height_, [this](std::size_t start, std::size_t end) {
//         for (std::size_t y = start; y < end; ++y) {
//             for (std::size_t x = 0; x < width_; ++x) {
//                 RGB& px = pixels_[y * width_ + x];

//             }
//         }
//     });
// }
