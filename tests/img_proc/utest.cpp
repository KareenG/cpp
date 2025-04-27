#include "mu_test.h"

#include "img_proc/rgb.hpp"
#include "img_proc/image.hpp"
#include "img_proc/image_proc.hpp"

#include <filesystem>
#include <fstream>
#include <cstdio>

/*------------------------------------------------------------------------------------------------------*/

template<typename T>
bool test_null_transform(const std::string& input_file, const std::string& output_file, size_t threads_num = 1)
{
    auto original = img_proc::image::image_loader<T>(input_file);

    img_proc::NullTransformer<T> null_transformer;
    auto transformed = null_transformer.transform_image(original, threads_num);

    img_proc::image::image_saver(output_file, transformed);

    auto reloaded = img_proc::image::image_loader<T>(output_file);

    return transformed == reloaded;
}

BEGIN_TEST(test_null_transformer)
    ASSERT_THAT(test_null_transform<uint16_t>("Trump.ppm", "copy_trump.ppm", 4));
    // convert copy_trump.ppm copy_trump.png
    ASSERT_THAT(test_null_transform<uint16_t>("kiyomizudera_temple.ppm", "copy_kiyomizudera_temple.ppm", 8));
    // convert copy_kiyomizudera_temple.ppm copy_kiyomizudera_temple.png
    ASSERT_THAT(test_null_transform<uint16_t>("vegetables.ppm", "copy_vegetables.ppm", 2));
    // convert copy_vegetables.ppm copy_vegetables.png
END_TEST

/*------------------------------------------------------------------------------------------------------*/

template<typename T>
bool test_reduce_colors(const std::string& input_file, const std::string& output_file, size_t color_num, size_t threads_num = 1)
{
    auto original = img_proc::image::image_loader<T>(input_file);

    img_proc::ColorReduction<T> color_reduct{color_num};
    auto reduced = color_reduct.transform_image(original, threads_num);

    img_proc::image::image_saver(output_file, reduced);

    auto reloaded = img_proc::image::image_loader<T>(output_file);

    return reduced == reloaded;
}

BEGIN_TEST(test_color_reduction)
    ASSERT_THAT(test_reduce_colors<uint16_t>("Trump.ppm", "rc_trump.ppm", 4, 2));
    // convert rc_trump.ppm rc_trump.png
    ASSERT_THAT(test_reduce_colors<uint16_t>("kiyomizudera_temple.ppm", "rc_kiyomizudera_temple.ppm", 8, 6));
    // convert rc_kiyomizudera_temple.ppm rc_kiyomizudera_temple.png
    ASSERT_THAT(test_reduce_colors<uint16_t>("vegetables.ppm", "rc_vegetables.ppm", 2, 7));
    // convert rc_vegetables.ppm rc_vegetables.png
END_TEST

/*------------------------------------------------------------------------------------------------------*/

template<typename T>
bool test_pixelate_single(const std::string& input_file, const std::string& output_file, size_t block_size, size_t threads_num = 1)
{
    auto original = img_proc::image::image_loader<T>(input_file);

    img_proc::Pixelator<T> pixelator{block_size};
    auto pixelated = pixelator.transform_image(original, threads_num);

    img_proc::image::image_saver(output_file, pixelated);

    auto reloaded = img_proc::image::image_loader<T>(output_file);

    return pixelated == reloaded;
}

BEGIN_TEST(test_pixelate)
    ASSERT_THAT(test_pixelate_single<uint16_t>("Trump.ppm", "px_trump.ppm", 4));
    // convert px_trump.ppm px_trump.png
    ASSERT_THAT(test_pixelate_single<uint16_t>("kiyomizudera_temple.ppm", "px_kiyomizudera_temple.ppm", 8));
    // convert px_kiyomizudera_temple.ppm px_kiyomizudera_temple.png
    ASSERT_THAT(test_pixelate_single<uint16_t>("vegetables.ppm", "px_vegetables.ppm", 6));
    // convert px_vegetables.ppm px_vegetables.png
END_TEST

/*------------------------------------------------------------------------------------------------------*/

template<typename T>
bool test_gauss(const std::string& input_file, const std::string& output_file, size_t kernel_size, double sigma, size_t threads_num = 1)
{
    auto original = img_proc::image::image_loader<T>(input_file);

    img_proc::GaussianBlur<T> blur{kernel_size, sigma};
    auto blurred = blur.transform_image(original, threads_num);

    img_proc::image::image_saver(output_file, blurred);

    auto reloaded = img_proc::image::image_loader<T>(output_file);

    return blurred == reloaded;
}

BEGIN_TEST(test_gaussian_blur)
    ASSERT_THAT(test_gauss<uint16_t>("Trump.ppm", "gb_trump.ppm", 11, 5.0, 8));
    // convert gb_trump.ppm gb_trump.png
    ASSERT_THAT(test_gauss<uint16_t>("kiyomizudera_temple.ppm", "gb_kiyomizudera_temple.ppm", 5, 1.6, 4));
    // convert gb_kiyomizudera_temple.ppm gb_kiyomizudera_temple.png
    ASSERT_THAT(test_gauss<uint16_t>("vegetables.ppm", "gb_vegetables.ppm", 7, 1.1, 10));
    // convert gb_vegetables.ppm gb_vegetables.png
END_TEST

/*------------------------------------------------------------------------------------------------------*/

BEGIN_SUITE(image_processing_tests)
    TEST(test_null_transformer)
    TEST(test_color_reduction)
    TEST(test_pixelate)
    TEST(test_gaussian_blur)
END_SUITE
