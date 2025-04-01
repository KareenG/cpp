#include <iostream>
#include <cstring> // for memset
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h> // for close
#include "palantir/udp/udp_server.hpp"

namespace palantir {

UdpServer::UdpServer(int port)
: port_(port) 
{
    socket_id_ = socket(AF_INET, SOCK_DGRAM, 0);
    if (socket_id_ < 0) {
        std::cerr << "Failed to create socket.\n";
        return;
    }

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(port_);

    if (bind(socket_id_, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "Failed to bind socket.\n";
        close(socket_id_);
        socket_id_ = -1;
    }
}

UdpServer::~UdpServer() 
{
    if (socket_id_ != -1) {
        close(socket_id_);
    }
}

std::string UdpServer::receive() 
{
    if (socket_id_ == -1) return "";

    char buffer[1024] = {0};
    struct sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    int len = recvfrom(socket_id_, buffer, sizeof(buffer) - 1, 0, (struct sockaddr *)&client_addr, &client_addr_len);
    if (len > 0) {
        buffer[len] = '\0';
        return std::string(buffer, len);
    }

    std::cerr << "Receive failed\n";
    return "";
}

void UdpServer::send_message(const std::string& message) 
{
    struct sockaddr_in client_addr; // Assuming client_addr is defined elsewhere if needed
    ssize_t sent_bytes = sendto(socket_id_, message.c_str(), message.size(), 0,
                                (const struct sockaddr *)&client_addr, sizeof(client_addr));
    if (sent_bytes < 0) {
        std::cerr << "Send failed\n";
        exit(EXIT_FAILURE);
    }
}

}       //  namespace palantir


// #include <iostream>
// #include <stdexcept>
// #include <string>
// #include <cstring> // for memset
// #include <sys/socket.h>
// #include <netinet/in.h>
// #include <arpa/inet.h>
// #include <unistd.h> // for close

// #include "palantir/udp/udp_server.hpp"


// namespace palantir {

// UdpServer::UdpServer(std::string const& ip, int port) : ip_(ip), port_(port) 
// {
//     socket_id_ = socket(AF_INET, SOCK_DGRAM, 0);
//     if (socket_id_ < 0) {
//         std::cerr << "Failed to create socket.\n";
//         return;
//     }

//     memset(&server_addr_, 0, sizeof(server_addr_));
//     server_addr_.sin_family = AF_INET;
//     server_addr_.sin_addr.s_addr = htonl(INADDR_ANY);
//     server_addr_.sin_port = htons(port_);

//     if (bind(socket_id_, (struct sockaddr *)&server_addr_, sizeof(server_addr_)) < 0) {
//         std::cerr << "Failed to bind socket.\n";
//         close(socket_id_);
//         socket_id_ = -1;
//     }
// }

// UdpServer::~UdpServer() 
// {
//     if (socket_id_ != -1) {
//         close(socket_id_);
//     }
// }

// // void UdpServer::start_listening() 
// // {
// //     if (socket_id_ == -1) return;

// //     char buffer[1024];
// //     while (true) {
// //         struct sockaddr_in client_addr;
// //         socklen_t client_addr_len = sizeof(client_addr);
// //         int len = recvfrom(socket_id_, buffer, sizeof(buffer) - 1, 0, (struct sockaddr *)&client_addr, &client_addr_len);
// //         if (len > 0) {
// //             buffer[len] = '\0';
// //             std::cout << "Received message: " << buffer << std::endl;
// //         }
// //     }
// // }

// std::string UdpServer::receive() 
// {
//     if (socket_id_ == -1) return "";

//     char buffer[1024] = {0};
//     struct sockaddr_in client_addr;
//     socklen_t client_addr_len = sizeof(client_addr);
//     int len = recvfrom(socket_id_, buffer, sizeof(buffer) - 1, 0, (struct sockaddr *)&client_addr, &client_addr_len);
//     if (len > 0) {
//         buffer[len] = '\0';
//         return std::string(buffer, len);
//     }

//     std::cerr << "Receive failed\n";
//     return "";
// }

// //DEBUG
// void UdpServer::send_message(const std::string& message) {
//     ssize_t sent_bytes = sendto(socket_id_, message.c_str(), message.size(), 0, 
//                                 (const struct sockaddr *)&server_addr_, sizeof(server_addr_));
//     if (sent_bytes < 0) {
//         perror("Send failed");
//         exit(EXIT_FAILURE);
//     }
// }

// }       //  namespace palantir