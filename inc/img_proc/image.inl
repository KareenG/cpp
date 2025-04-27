#pragma once

#include <fstream>
#include <stdexcept>

#include "img_proc/image.hpp"
#include "img_proc/img_proc_exceptions.hpp"

namespace img_proc::image {

template<typename T>
Image<T>::Image(size_t height, size_t width, size_t max_color)
: height_{height}
, width_{width}
, max_color_{max_color}
, pixels_(height * width)
{
}

template<typename T>
Image<T>::Image(std::vector<RGB<T>>&& vec, size_t height, size_t width, size_t max_color)
: height_{height}
, width_{width}
, max_color_{max_color}
, pixels_(std::move(vec))
{
}

template<typename T>
RGB<T>& Image<T>::operator[](size_t index)
{
    return pixels_[index];
}

template<typename T>
const RGB<T>& Image<T>::operator[](size_t index) const
{
    return pixels_[index];
}

template<typename T>
RGB<T>& Image<T>::operator()(size_t row, size_t column)
{
    if (row >= height_ || column >= width_) {
        throw OutOfBoundsException();
    }
    return pixels_[row * width_ + column];
}

template<typename T>
RGB<T> Image<T>::operator()(size_t row, size_t column) const
{
    if (row >= height_ || column >= width_) {
        throw OutOfBoundsException();
    }
    return pixels_[row * width_ + column];
}

template<typename T>
bool Image<T>::operator==(const Image<T>& other) const noexcept
{
    return height_ == other.height_ &&
           width_ == other.width_ &&
           max_color_ == other.max_color_ &&
           pixels_ == other.pixels_;
}

template<typename T>
void Image<T>::resize(size_t new_height, size_t new_width, size_t new_max_color)
{
    height_ = new_height;
    width_ = new_width;
    max_color_ = new_max_color;
    pixels_.resize(height_ * width_);
}

template<typename T>
size_t Image<T>::size() const noexcept
{
    return width_ * height_;
}

template<typename T>
void Image<T>::print_image() const
{
    for (size_t row = 0; row < height_; ++row) {
        for (size_t col = 0; col < width_; ++col) {
            std::cout << operator()(row, col) << " ";
        }
        std::cout << '\n';
    }
}

template<typename T>
size_t Image<T>::height() const noexcept
{
    return height_;
}

template<typename T>
size_t Image<T>::width() const noexcept
{
    return width_;
}

template<typename T>
size_t Image<T>::max_color() const noexcept
{
    return max_color_;
}

template<typename T>
Image<T> image_loader(const std::string& file_path)
{
    std::ifstream in(file_path);
    if (!in) {
        throw FileOpenException(file_path);
    }
    return image_loader<T>(in);
}

template<typename T>
Image<T> image_loader(std::istream& is)
{
    if (!is) {
        throw InputStreamException();
    }

    std::string header;
    if (!(is >> header) || header != "P3") {
        throw FileASCIIException();
    }

    while (is.peek() == '#') {
        std::string skip;
        std::getline(is, skip);
    }

    size_t width, height, max_color;
    if (!(is >> width >> height) || width == 0 || height == 0) {
        throw FileFormatException();
    }

    if (!(is >> max_color) || max_color == 0) {
        throw FileFormatException();
    }

    std::vector<RGB<T>> vec(width * height);

    for (auto& pixel : vec) {
        T r, g, b;
        if (!(is >> r >> g >> b)) {
            throw FileFormatException();
        }
        pixel = RGB<T>(r, g, b);
    }

    return Image<T>(std::move(vec), height, width, max_color);
}

template<typename T>
void image_saver(const std::string& file_path, Image<T>& image)
{
    std::ofstream out(file_path);
    if (!out) {
        throw FileOpenException(file_path);
    }
    image_saver(out, image);
}

template<typename T>
void image_saver(std::ostream& os, Image<T>& image)
{
    if (!os) {
        throw OutputStreamException();
    }

    os << "P3\n" << image.width() << ' ' << image.height() << '\n' << image.max_color() << '\n';
    for (size_t row = 0; row < image.height(); ++row) {
        for (size_t col = 0; col < image.width(); ++col) {
            os << image(row, col);
        }
        os << '\n';
    }
}

} // namespace img_proc::image
















// #pragma once

// #include <type_traits> // For static_assert on T
// #include <fstream>

// #include "img_proc/image.hpp"
// #include "img_proc/img_proc_exceptions.hpp"

// //#include "img_proc/loader_saver_ppm.hpp"

// namespace img_proc::image {

// template<typename T>
// Image<T>::Image(size_t height, size_t width, size_t max_color)
// : height_{height}
// , width_{width}
// , max_color_{max_color}
// , pixels_(height * width)
// {
// }

// template<typename T>
// Image<T>::Image(std::vector<RGB<T>>&& vec, size_t height, size_t width, size_t max_color)
// : height_{height}
// , width_{width}
// , max_color_{max_color}
// , pixels_{std::move(vec)}
// {
// }

// // template<typename T>
// // void Image<T>::load_bulk(std::vector<RGB<T>>&& vec, ImageDetail const& details)
// // {
// //     pixels_ = std::move(vec);
// //     height_ = details.height_;
// //     width_ = details.width_;
// //     max_color_ = details.max_color_;
// // }

// template<typename T>
// RGB<T>& Image<T>::operator[](size_t index)
// {
//     return pixels_[index];
// }

// template<typename T>
// RGB<T> const& Image<T>::operator[](size_t index) const
// {
//     return pixels_[index];
// }

// template<typename T>
// void Image<T>::resize(size_t new_height, size_t new_width, size_t new_max_color)
// {
//     height_ = new_height;
//     width_ = new_width;
//     max_color_ = new_max_color;
//     pixels_.resize(height_ * width_);
// }

// template<typename T>
// size_t Image<T>::size() const noexcept
// {
//     return width_ * height_;
// }

// template<typename T>
// void Image<T>::print_image() const
// {
//     for (size_t i = 0; i < height_; ++i) {
//         for (size_t j = 0; j < width_; ++j) {
//             //size_t index = at_index(i, j);
//             //std::cout << pixels_[index] << " ";
//             std::cout << pixels_(i, j) << " ";
//         }
//         std::cout << '\n';
//     }
// }

// template<typename T>
// size_t Image<T>::height() const noexcept
// {
//     return height_;
// }

// template<typename T>
// size_t Image<T>::width() const noexcept
// {
//     return width_;
// }

// template<typename T>
// size_t Image<T>::max_color() const noexcept
// {
//     return max_color_;
// }

// // template<typename T>
// // size_t Image<T>::at_index(size_t row, size_t column) const
// // {
// //     if (row >= height_ || column >= width_) {
// //         throw OutOfBoundsException();//std::out_of_range("Image<T>::at_index: Row or column out of range");
// //     }
// //     return row * width_ + column;
// // }

// template<typename T>
// RGB<T> Image<T>::operator()(size_t row, size_t column) const
// {
//     if (row >= height_ || column >= width_) {
//         throw OutOfBoundsException();
//     }
//     return pixels_[row * width_ + column];
// }

// template<typename T>
// RGB<T>& Image<T>::operator()(size_t row, size_t column)
// {
//     if (row >= height_ || column >= width_) {
//         throw OutOfBoundsException();
//     }
//     return pixels_[row * width_ + column];
// }

// template<typename T>
// bool Image<T>::operator==(const Image<T>& other) const noexcept
// {
//     return width_ == other.width_
//         && height_ == other.height_
//         && max_color_ == other.max_color_
//         && pixels_ == other.pixels_;
// }

// template<typename T>
// Image<T> image_loader(std::string const& file_path)
// {
//     std::ifstream in(file_path);
//     if (!in) {
//         throw FileOpenException(file_path);
//     }
//     return image_loader<T>(in);
// }

// template<typename T>
// Image<T> image_loader(std::istream& is)
// {
//     if (!is) {
//         throw InputStreamException();
//     }

//     //ImageDetail details{};
//     size_t height;
//     size_t width;
//     size_t max_color;

//     std::string header;
//     is >> header;

//     if (header != "P3") {
//         throw FileASCIIException();
//     }

//     while (is.peek() == '#') {
//         std::string skip;
//         std::getline(is, skip);
//     }

//     // Read width and height
//     //if (!(is >> details.width_ >> details.height_)) {
//     if (!(is >> width >> height)) {
//         throw FileFormatException(); // width/height missing or invalid
//     }

//     // Validate dimensions
//     // if (details.width_ == 0 || details.height_ == 0) {
//     if (width == 0 || height == 0) {
//         throw FileFormatException(); // nonsensical dimensions
//     }

//     // Read max color value
//     //if (!(is >> details.max_color_)) {
//     if(!(is >> max_color)) {
//         throw FileFormatException(); // missing or invalid max color
//     }

//     // if (details.max_color_ == 0) {
//     if(max_color == 0) {
//         throw FileFormatException(); // nonsensical max color
//     }

//     // std::vector<RGB<T>> vec(details.width_ * details.height_);
//     std::vector<RGB<T>> vec(width * height);

//     for (size_t i = 0; i < vec.size(); ++i) {
//         T r, g, b;
//         //is >> r >> g >> b;
//         //vec[i] = RGB<T>(static_cast<T>(r), static_cast<T>(g), static_cast<T>(b));
//         if (!(is >> r >> g >> b)) {
//             throw FileFormatException(); // incomplete pixel
//         }
//         vec[i] = RGB<T>{r, g, b};
//     }

//     // return image<T>{std::move(vec), details};
//     return image<T>{std::move(vec), height, width, max_color};
// }

// template<typename T>
// void image_saver(std::string const& file_path, Image<T>& image)
// {
//     std::ofstream out(file_path);
//     if (!out) {
//         throw FileOpenException(file_path);
//     }
//     image_saver(out, image);
// }

// template<typename T>
// void image_saver(std::ostream& os, Image<T>& image)
// {
//     if (!os) {
//         throw OutputStreamException();
//     }

//     os << "P3\n"
//        << image.width() << ' ' << image.height() << '\n'
//        << image.max_color() << '\n';

//     for (size_t row = 0; row < image.height(); ++row) {
//         for (size_t col = 0; col < image.width(); ++col) {
//             //os << image[image.at_index(row, col)];
//             os << image(row, col);
//         }
//         os << '\n';
//     }
// }

// } // namespace image::img_proc
