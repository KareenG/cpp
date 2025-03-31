#pragma once

#include <fstream>

#include "palantir/message_source/message_source_abstract.hpp"

namespace palantir {

class FileSource : public MessageSourceAbstract {
private:
    std::string file_name_{};
    std::ifstream file_stream_;

public:
    explicit FileSource(std::string const& file_name);
    
    virtual ~FileSource() override;

    virtual std::string get_message() override;
    virtual bool is_fully_processed() const override;
};

}       //  namespace palantir

