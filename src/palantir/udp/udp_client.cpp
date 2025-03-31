#include <iostream>
#include <cstring>
#include <unistd.h> // for close
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "palantir/udp/udp_client.hpp"

namespace palantir {

UdpClient::UdpClient(const std::string& ip, int port)
: ip_(ip)
, port_(port) 
{
    socket_id_ = socket(AF_INET, SOCK_DGRAM, 0);
    if (socket_id_ < 0) {
        std::cerr << "Failed to create socket." << '\n';
    }

    memset(&server_addr_, 0, sizeof(server_addr_));
    server_addr_.sin_family = AF_INET;
    server_addr_.sin_addr.s_addr = inet_addr(ip_.c_str());
    server_addr_.sin_port = htons(port_);
}

UdpClient::~UdpClient() {
    if (socket_id_ != -1) {
        close(socket_id_);
    }
}

void UdpClient::send_message(const std::string& message)
{
    sendto(socket_id_, message.c_str(), message.length(), 0, (struct sockaddr *)&server_addr_, sizeof(server_addr_));
}

//DEBUG
std::string UdpClient::receive_message() {
    char buffer[1024];
    socklen_t len = sizeof(server_addr_);
    ssize_t n = recvfrom(socket_id_, buffer, sizeof(buffer) - 1, 0, (struct sockaddr *)&server_addr_, &len);
    if (n < 0) {
        std::cerr << "Receive failed\n";
        return "";
    }
    buffer[n] = '\0';
    return std::string(buffer);
}

}       //  namespace palantir