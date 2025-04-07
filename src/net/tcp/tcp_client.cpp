#include <iostream>
#include <cstring> // for memset
#include <unistd.h> // for close
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cassert>

#include "palantir/tcp/tcp_client.hpp"

namespace palantir {

TcpClient::TcpClient(const std::string& ip, int port)
: ip_{ip}
, port_{port}
, socket_id_{-1}
, connected_{false}
{
}

TcpClient::~TcpClient() 
{
    close_connection();
}

bool TcpClient::connect_to_server() {
    if (connected_) {
        std::cerr << "Already connected to server.\n";
        return false;
    }

    socket_id_ = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_id_ < 0) {
        std::cerr << "Failed to create socket.\n";
        return false;
    }

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(ip_.c_str());
    server_addr.sin_port = htons(port_);

    if (connect(socket_id_, reinterpret_cast<struct sockaddr*>(&server_addr), sizeof(server_addr)) < 0) {
        std::cerr << "Connection failed.\n";
        close(socket_id_);
        socket_id_ = -1;
        return false;
    }

    connected_ = true;
    std::cout << "Connected to server.\n";
    return true;
}

void TcpClient::close_connection() {
    if (socket_id_ != -1) {
        close(socket_id_);
        socket_id_ = -1;
        connected_ = false;
        std::cout << "Connection closed.\n";
    }
}

void TcpClient::send_message(const std::string& message) {
    if (!connected_) {
        std::cerr << "Not connected to server.\n";
        return;
    }

    if (send(socket_id_, message.c_str(), message.length(), 0) < 0) {
        std::cerr << "Send failed.\n";
        close_connection();
    }
}

std::string TcpClient::receive_message() {
    if (!connected_) {
        std::cerr << "Not connected to server.\n";
        return "";
    }

    char buffer[1024];
    ssize_t n = recv(socket_id_, buffer, sizeof(buffer) - 1, 0);
    if (n < 0) {
        std::cerr << "Receive failed.\n";
        close_connection();
        return "";
    }
    
    buffer[n] = '\0';
    return std::string(buffer);
}

} // namespace palantir
