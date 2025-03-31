#pragma once

#include <iostream>
#include <string>
#include "palantir/message_source/message_source_abstract.hpp"

namespace palantir {

class Console : public MessageSourceAbstract {
private:
    std::istream& input_stream_;

public:
    Console(std::istream& input = std::cin);

    virtual ~Console() override = default;

    virtual std::string get_message() override;

    virtual bool is_fully_processed() const override;

};

} // namespace palantir
