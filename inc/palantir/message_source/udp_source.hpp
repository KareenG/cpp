#pragma once

#include "palantir/message_source/message_source_abstract.hpp"
#include "palantir/udp/udp_server.hpp"

namespace palantir {

class UdpSource : public MessageSourceAbstract {
private:
    UdpServer udp_des_;

public:
    explicit UdpSource(std::string const& ip, int port);
    
    virtual ~UdpSource() override = default;

    virtual std::string get_message() override;
    virtual bool is_fully_processed() const override;

    // DEBUG
    void send_message(const std::string& message);
};

}       //  namespace palantir

