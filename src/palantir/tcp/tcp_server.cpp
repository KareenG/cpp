#include <iostream>
#include <unistd.h> // for close
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

#include "palantir/tcp/tcp_server.hpp"

namespace palantir {

TcpServer::TcpServer(int port)
: port_(port)
, socket_id_(-1) 
{
    // Create the socket
    socket_id_ = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_id_ < 0) {
        printf("Failed to create socket.\n");
        return;
    }

    // Set up the server address structure
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port_);

    // Bind the socket to the address
    if (bind(socket_id_, reinterpret_cast<struct sockaddr*>(&server_addr), sizeof(server_addr)) < 0) {
        printf("Binding failed.\n");
        close(socket_id_);
        return;
    }

    // Start listening for incoming connections
    if (listen(socket_id_, 1) < 0) {
        printf("Listen failed.\n");
        close(socket_id_);
        return;
    }

    //printf("Server listening on port %d\n", port_);
}

TcpServer::~TcpServer() {
    if (socket_id_ != -1) {
        close(socket_id_);
    }
}

int TcpServer::accept_client() {
    // Accept incoming client connection
    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);
    int client_socket = accept(socket_id_, reinterpret_cast<struct sockaddr*>(&client_addr), &client_len);
    if (client_socket < 0) {
        printf("Accept failed.\n");
        return -1;
    } else {
        printf("Client connected.\n");
        return client_socket;
    }
}

std::string TcpServer::receive(int client_socket) {
    // Receive message from the client
    char buffer[1024];
    ssize_t n = recv(client_socket, buffer, sizeof(buffer) - 1, 0);
    if (n > 0) {
        buffer[n] = '\0';
        return std::string(buffer);
    } else {
        printf("Receive failed.\n");
        return "";
    }
}

void TcpServer::send_message(int client_socket, const std::string& message) {
    // Send a response back to the client
    send(client_socket, message.c_str(), message.length(), 0);
    printf("Sent to client: %s\n", message.c_str());
}

} // namespace palantir
