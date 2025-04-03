#include <iostream>
#include <unistd.h>

#include "palantir/message_source/tcp_source.hpp"

namespace palantir {

TcpSource::TcpSource(int port)
: tcp_server_(port)
, client_socket_(-1)
, fully_processed_(false) 
{
    // Accept the client connection
    client_socket_ = tcp_server_.accept_client();
    if (client_socket_ < 0) {
        std::cerr << "Failed to accept client connection.\n";
    }
}

TcpSource::~TcpSource() {
    // Close the client socket if it is open
    if (client_socket_ != -1) {
        close(client_socket_);
    }
}

std::string TcpSource::get_message() {
    // Get the message from the connected client
    if (client_socket_ != -1) {
        return tcp_server_.receive(client_socket_);
    } else {
        std::cerr << "No active client connection.\n";
        return "";
    }
}

bool TcpSource::is_fully_processed() const {
    // Assuming one message is processed at a time
    return fully_processed_;
}

} // namespace palantir
