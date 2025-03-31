#pragma once

#include <fstream>

#include "palantir/message_destination/message_destination_abstract.hpp"

namespace palantir {

class FileDestination : public MessageDestinationAbstract {
private:
    std::string file_name_;
    std::ofstream file_stream_;

public:
    explicit FileDestination(const std::string& file_name);
    virtual ~FileDestination() override;

    virtual void send_message(const std::string& message) override;
};

}       //  namespace palantir

