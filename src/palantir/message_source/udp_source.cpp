#include <iostream>
#include <fstream>

#include "palantir/message_source/udp_source.hpp"

namespace palantir {

UdpSource::UdpSource(int port) 
: udp_source_{port}
, is_done_{false}
{
}

std::string UdpSource::get_message() 
{
    std::string message = udp_source_.receive();
    if(message.find("#EOT#") != std::string::npos) {
        is_done_ = true;
    }
    return message;
}

bool UdpSource::is_fully_processed() const 
{
    return is_done_;
}

//DEBUG
void UdpSource::send_message(const std::string& message) 
{
    std::ofstream file("test_udp_source.txt", std::ios::app); // Open in append mode
    if (file.is_open()) {
        file << message << '\n';
        file.close();
    } else {
        std::cerr << "Failed to open file for writing." << '\n';
    }

    udp_source_.send_message(message);
}

};