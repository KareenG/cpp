#pragma once

#include "palantir/message_destination/message_destination_abstract.hpp"
#include "palantir/udp/udp_client.hpp"

namespace palantir {

class UdpDestination : public MessageDestinationAbstract {
private:
    UdpClient udp_client_;

public:
    explicit UdpDestination(const std::string& ip, int port);
    virtual ~UdpDestination() override {}

    virtual void send_message(const std::string& message) override;

    // DEBUG
    std::string receive_message();
};

}       //  namespace palantir

