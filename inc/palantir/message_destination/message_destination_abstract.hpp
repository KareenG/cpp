#pragma once

#include <stddef.h>
#include <string>

namespace palantir {

class MessageDestinationAbstract {
public:
    MessageDestinationAbstract() = default;

    virtual ~MessageDestinationAbstract() = default;

    virtual void send_message(std::string const& mes) = 0;

protected:
    MessageDestinationAbstract(MessageDestinationAbstract const& other) = default;

    MessageDestinationAbstract& operator=(MessageDestinationAbstract const& other) = default;
};

}       //  namespace palantir

