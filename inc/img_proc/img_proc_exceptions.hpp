#pragma once

#include <stdexcept>
#include <string>

namespace img_proc {

/**
 * @brief Thrown when a file cannot be opened for reading or writing.
 * @throws std::runtime_error
 */
class FileOpenException : public std::runtime_error {
public:
    /**
     * @brief Constructs the exception with the problematic file path.
     * @param path The path to the file that could not be opened.
     */
    explicit FileOpenException(const std::string& path);
};

/**
 * @brief Thrown when an invalid input stream is detected.
 * @throws std::invalid_argument
 */
class InputStreamException : public std::invalid_argument {
public:
    explicit InputStreamException();
};

/**
 * @brief Thrown when an invalid output stream is detected.
 * @throws std::invalid_argument
 */
class OutputStreamException : public std::invalid_argument {
public:
    explicit OutputStreamException();
};

/**
 * @brief Thrown when a PPM file is not in ASCII P3 format.
 * @throws std::invalid_argument
 */
class FileASCIIException : public std::invalid_argument {
public:
    explicit FileASCIIException();
};

/**
 * @brief Thrown when when a file has an invalid or corrupted format.
 * @throws std::invalid_argument
 * 
 * This exception is typically thrown during file parsing or reading operations
 * when the structure or contents of the file do not match the expected format.
 */
class FileFormatException : public std::invalid_argument {
public:
    explicit FileFormatException();
};

/**
 * @brief Thrown when an invalid kernel size is given for Gaussian blur.
 * @throws std::invalid_argument
 */
class InvalidKernelSizeException : public std::invalid_argument {
public:
    explicit InvalidKernelSizeException();
};

class OutOfBoundsException : public std::out_of_range {
public:
    explicit OutOfBoundsException();
};

/*---------------------------------------------------------*/
/*                      Implementations                    */
/*---------------------------------------------------------*/

inline FileOpenException::FileOpenException(const std::string& path)
: std::runtime_error("Failed to open file: " + path)
{
}

inline InputStreamException::InputStreamException()
: std::invalid_argument("Invalid input stream")
{
}

inline OutputStreamException::OutputStreamException()
: std::invalid_argument("Invalid output stream")
{
}

inline FileASCIIException::FileASCIIException()
: std::invalid_argument("Only P3 PPM (ASCII) is supported")
{
}

inline FileFormatException::FileFormatException()
: std::invalid_argument("Invalid or corrupted file format.") 
{
}

inline InvalidKernelSizeException::InvalidKernelSizeException()
: std::invalid_argument("Gaussian kernel size must be odd (3,5,7,9...)")
{
}

inline OutOfBoundsException::OutOfBoundsException()
: std::out_of_range("Image<T>::at_index: Row or column out of range")
{
}

} // namespace img_proc
