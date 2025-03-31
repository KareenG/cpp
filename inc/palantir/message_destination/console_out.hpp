#pragma once

#include <iostream>
#include <string>
#include "palantir/message_destination/message_destination_abstract.hpp"

namespace palantir {

class ConsoleOutput : public MessageDestinationAbstract {
private:
    std::ostream& output_stream_;

public:
    ConsoleOutput(std::ostream& output = std::cout);
    virtual ~ConsoleOutput() override = default;

    virtual void send_message(const std::string& message) override;

};

} // namespace palantir
