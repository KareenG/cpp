#include <iostream>
#include <unistd.h> // for close
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

#include "net/exceptions.hpp"
#include "net/tcp/tcp_server.hpp"
#include "net/tcp/tcp_client.hpp"
namespace net {

TcpServer::TcpServer(int port)
//: port_(port) 
{
    try {
        setup_server_socket(port);
    } catch (...) { //const  std::exception& e
        //close(server_socket_);
        throw;
    }
}

TcpServer::~TcpServer() noexcept 
{
    close(server_socket_);
}

void TcpServer::setup_server_socket(int port) 
{
    server_socket_ = socket(AF_INET, SOCK_STREAM, 0);
    //if (server_socket_ < 0) {
    int optval = 1;
    if (setsockopt(server_socket_, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) < 0) {
        throw net::CreateSocketException(errno);
    }

    sockaddr_in server_addr{};
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);

    if (bind(server_socket_, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        throw BindException(errno);
    }

    if (listen(server_socket_, SOMAXCONN) < 0) {
        throw ListenException(errno);//, "Failed to listen on socket");
    }
}

TcpClient TcpServer::accept_client() 
{
    sockaddr_in client_addr{};
    socklen_t client_len = sizeof(client_addr);
    int client_socket = accept(server_socket_, (struct sockaddr*)&client_addr, &client_len);
    if (client_socket < 0) {
        throw AcceptException(errno);//, "Failed to accept client");
    }
    return TcpClient(client_socket);
}

} // namespace net
