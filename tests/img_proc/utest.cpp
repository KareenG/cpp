#include "mu_test.h"

#include "imag_proc/image_proc.hpp"
#include "imag_proc/rgb.hpp"

#include <filesystem>
#include <fstream>
#include <cstdio>

/**
 * @brief Creates a small 4x4 PPM (P6) test image for unit testing.
 * @param file_path Path to save the generated image.
 */
inline void create_test_image(const std::string& file_path) {
    std::ofstream out(file_path, std::ios::binary);
    if (!out) {
        throw std::runtime_error("Cannot create test image");
    }

    out << "P6\n4 4\n255\n";

    std::vector<unsigned char> data = {
        0x10, 0x10, 0x10,  0x80, 0x80, 0x80,  0xFF, 0xFF, 0xFF,  0x00, 0x00, 0x00,
        0x80, 0x80, 0x80,  0xFF, 0xFF, 0xFF,  0x10, 0x10, 0x10,  0x00, 0x00, 0x00,
        0xFF, 0x00, 0x00,  0x00, 0xFF, 0x00,  0x00, 0x00, 0xFF,  0xFF, 0xFF, 0x00,
        0xCC, 0xCC, 0xCC,  0x22, 0x22, 0x22,  0x99, 0x99, 0x99,  0x44, 0x44, 0x44,
    };

    out.write(reinterpret_cast<const char*>(data.data()), data.size());
}

BEGIN_TEST(reduce_colors_generated_image)
    //create_test_image("before.ppm");

    ImageProcessor<RGB> image("bclc.ppm");
    image.reduce_colors(4);
    image.save("after.ppm");

    ASSERT_THAT(std::filesystem::exists("bclc.ppm"));
    ASSERT_THAT(std::filesystem::exists("after.ppm"));

    // then run this to see the before and after affect
    // convert bclc.ppm before.png
    // convert after.ppm after.png
    
    // To use this feature run:
    // sudo apt update
    // sudo apt install imagemagick

    std::filesystem::remove("generated.ppm");
    std::filesystem::remove("tmp_out.ppm");
END_TEST

BEGIN_SUITE(image_processing_tests)
    TEST(reduce_colors_generated_image)
END_SUITE