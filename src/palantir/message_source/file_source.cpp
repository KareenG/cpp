#include <iostream>
#include <filesystem>

#include "palantir/message_source/file_source.hpp"

namespace palantir {

FileSource::FileSource(std::string const& file_name)
: file_name_{file_name}
, file_stream_{file_name}
{
    if(!file_stream_) {
        std::cerr << "Failed to open file: " << file_name << '\n';
        exit(1);
    }
}

FileSource::~FileSource()
{
    if (file_stream_.is_open()) {
        file_stream_.close();
    }
}

std::string FileSource::get_message()
{
    std::string message_line;
    if(getline(file_stream_, message_line)) {
        message_line.push_back('\n');
        return message_line;
    }
    return "";
}

bool FileSource::is_fully_processed() const
{
    return file_stream_.eof();
}

};