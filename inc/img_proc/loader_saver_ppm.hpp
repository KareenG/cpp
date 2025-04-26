#pragma once

#include <string>
#include <istream>
#include <ostream>

#include "img_proc/image.hpp"

namespace img_proc {

/**
 * @brief Provides functions for loading and saving images in ASCII PPM (P3) format.
 */
namespace loader {

/**
 * @brief Loads an image from a file path.
 * @throws FileOpenException if the file cannot be opened.
 * @throws FileASCIIException if the file format is not P3.
 * @throws InputStreamException if the file content is invalid.
 */
template<typename T>
void ImageLoader(std::string const& file_path, Image<T>& image);

/**
 * @brief Loads an image from an input stream.
 * @throws FileASCIIException if the stream does not contain a valid P3 PPM image.
 * @throws InputStreamException if the stream is invalid.
 */
template<typename T>
void ImageLoader(std::istream& is, Image<T>& image);

} // namespace loader

namespace saver {

/**
 * @brief Saves an image to a file path.
 * @throws FileOpenException if the file cannot be opened for writing.
 * @throws OutputStreamException if writing to the file fails.
 */
template<typename T>
void ImageSaver(std::string const& file_path, Image<T>& image);

/**
 * @brief Saves an image to an output stream.
 * @throws OutputStreamException if the output stream is invalid.
 */
template<typename T>
void ImageSaver(std::ostream& os, Image<T>& image);

} // namespace saver

} // namespace img_proc

#include "img_proc/loader_saver_ppm.inl"
