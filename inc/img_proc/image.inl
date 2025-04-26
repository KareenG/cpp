#pragma once

#include "img_proc/image.hpp"
#include <algorithm> // for std::copy

namespace img_proc {

template<typename T>
Image<T>::Image(size_t height, size_t width, size_t max_val)
: height_{height}
, width_{width}
, max_val_{max_val}
, pixels_(height * width)
{
}

template<typename T>
Image<T>::Image(std::vector<RGB<T>>&& vec, size_t height, size_t width, size_t max_val)
: height_{height}
, width_{width}
, max_val_{max_val}
, pixels_{std::move(vec)}
{
}

// -----------------------------------------------
// Copy constructor (deep copy)
template<typename T>
Image<T>::Image(Image const& other)
: height_{other.height_}
, width_{other.width_}
, max_val_{other.max_val_}
, pixels_{other.pixels_}
{
}

// Move constructor
template<typename T>
Image<T>::Image(Image&& other) noexcept
: height_{other.height_}
, width_{other.width_}
, max_val_{other.max_val_}
, pixels_{std::move(other.pixels_)}
{
    other.height_ = 0;
    other.width_ = 0;
    other.max_val_ = 255;
}

// Copy assignment (deep copy)
template<typename T>
Image<T>& Image<T>::operator=(Image const& other)
{
    if (this != &other) {
        height_ = other.height_;
        width_ = other.width_;
        max_val_ = other.max_val_;
        pixels_ = other.pixels_;
    }
    return *this;
}

// Move assignment
template<typename T>
Image<T>& Image<T>::operator=(Image&& other) noexcept
{
    if (this != &other) {
        height_ = other.height_;
        width_ = other.width_;
        max_val_ = other.max_val_;
        pixels_ = std::move(other.pixels_);

        other.height_ = 0;
        other.width_ = 0;
        other.max_val_ = 255;
    }
    return *this;
}
// -----------------------------------------------

template<typename T>
void Image<T>::load_bulk(std::vector<RGB<T>>&& vec, ImageDetail const& details)
{
    pixels_ = std::move(vec);
    height_ = details.height_;
    width_ = details.width_;
    max_val_ = details.max_val_;
}

template<typename T>
RGB<T>& Image<T>::operator[](size_t index)
{
    return pixels_[index];
}

template<typename T>
RGB<T> const& Image<T>::operator[](size_t index) const
{
    return pixels_[index];
}

template<typename T>
void Image<T>::resize(size_t new_height, size_t new_width, size_t new_max_val)
{
    height_ = new_height;
    width_ = new_width;
    max_val_ = new_max_val;
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
    for (size_t i = 0; i < height_; ++i) {
        for (size_t j = 0; j < width_; ++j) {
            size_t index = at_index(i, j);
            std::cout << pixels_[index] << " ";
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
size_t Image<T>::max_val() const noexcept
{
    return max_val_;
}

template<typename T>
size_t Image<T>::at_index(size_t row, size_t column) const noexcept
{
    return row * width_ + column;
}

template<typename T>
bool Image<T>::operator==(const Image<T>& other) const noexcept
{
    return width_ == other.width_
        && height_ == other.height_
        && max_val_ == other.max_val_
        && pixels_ == other.pixels_;
}

} // namespace img_proc
