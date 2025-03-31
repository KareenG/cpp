#pragma once

#include <string>

namespace palantir {

class MessageSourceAbstract {
public:
    MessageSourceAbstract() = default;
    
    virtual ~MessageSourceAbstract() = default;

    virtual std::string get_message() = 0;

    virtual bool is_fully_processed() const = 0;

protected:
    MessageSourceAbstract(MessageSourceAbstract const& other) = default;
    MessageSourceAbstract& operator=(MessageSourceAbstract const& other) = default;
};

}       //  namespace palantir

