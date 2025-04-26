#pragma once

#include <fstream>

#include "img_proc/loader_saver_ppm.hpp"
#include "img_proc/img_proc_exceptions.hpp"

namespace img_proc {

namespace loader {

template<typename T>
void ImageLoader(std::istream& is, Image<T>& image)
{
    if (!is) {
        throw InputStreamException();
    }

    ImageDetail details{};
    std::string header;
    is >> header;

    if (header != "P3") {
        throw FileASCIIException();
    }

    while (is.peek() == '#') {
        std::string skip;
        std::getline(is, skip);
    }

    is >> details.width_ >> details.height_;
    is >> details.max_val_;

    std::vector<RGB<T>> vec(details.width_ * details.height_);

    for (size_t i = 0; i < vec.size(); ++i) {
        int r, g, b;
        is >> r >> g >> b;
        vec[i] = RGB<T>(static_cast<T>(r), static_cast<T>(g), static_cast<T>(b));
    }

    image.load_bulk(std::move(vec), details);
}

template<typename T>
void ImageLoader(std::string const& file_path, Image<T>& image)
{
    std::ifstream in(file_path);
    if (!in) {
        throw FileOpenException(file_path);
    }
    ImageLoader(in, image);
}

} // namespace loader

namespace saver {

template<typename T>
void ImageSaver(std::ostream& os, Image<T>& image)
{
    if (!os) {
        throw OutputStreamException();
    }

    os << "P3\n"
       << image.width() << ' ' << image.height() << '\n'
       << image.max_val() << '\n';

    for (size_t row = 0; row < image.height(); ++row) {
        for (size_t col = 0; col < image.width(); ++col) {
            os << image[image.at_index(row, col)];
        }
        os << '\n';
    }
}

template<typename T>
void ImageSaver(std::string const& file_path, Image<T>& image)
{
    std::ofstream out(file_path);
    if (!out) {
        throw FileOpenException(file_path);
    }
    ImageSaver(out, image);
}

} // namespace saver

} // namespace img_proc
