#include <iostream>
#include <filesystem>

#include "palantir/message_destination/file_destination.hpp"

namespace palantir {

FileDestination::FileDestination(const std::string& file_name)
: file_name_(file_name) {
file_stream_.open(file_name_, std::ios::out | std::ios::app);
if (!file_stream_.is_open()) {
    std::cerr << "Failed to open file: " << file_name_ << '\n';
}
}

FileDestination::~FileDestination() {
    if (file_stream_.is_open()) {
        file_stream_.close();
    }
}

void FileDestination::send_message(const std::string& message) {
    if (!file_stream_.is_open()) {
        std::cerr << "Attempt to write to a closed file stream." << '\n';
    }
    file_stream_ << message << std::endl;
}

};