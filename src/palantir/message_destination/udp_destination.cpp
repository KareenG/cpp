#include "palantir/message_destination/udp_destination.hpp"

namespace palantir
{

UdpDestination::UdpDestination(const std::string& ip, int port)
: udp_client_(ip, port) 
{
}

void UdpDestination::send_message(const std::string& message) 
{
    udp_client_.send_message(message);
}

//DEBUG
std::string UdpDestination::receive_message() {
    return udp_client_.receive_message();
}
 
} // namespace palantir
