#include <iostream>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h> // for close
#include <cstring> // for memset

#include "palantir/message_source/udp_source.hpp"

namespace palantir {

UdpSource::UdpSource(std::string const& ip, int port)
: udp_des_{ip, port}
{
}

std::string UdpSource::get_message() 
{
    return udp_des_.receive();
}

bool UdpSource::is_fully_processed() const 
{
    return false;
}

//DEBUG
void UdpSource::send_message(const std::string& message) 
{
    udp_des_.send_message(message);
}

};