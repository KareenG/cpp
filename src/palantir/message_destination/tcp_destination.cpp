#include <iostream>

#include "palantir/message_destination/tcp_destination.hpp"

namespace palantir {

TcpDestination::TcpDestination(const std::string& ip, int port)
: tcp_client_(ip, port) {
    // Attempt to connect to the server
    if (!tcp_client_.connect_to_server()) {
        std::cerr << "Failed to connect to server in TcpDestination constructor." << std::endl;
    }
}

TcpDestination::~TcpDestination() {
    // Ensure that the connection is closed when TcpDestination is destroyed
    tcp_client_.close_connection();
}

void TcpDestination::send_message(const std::string& message) {
    // Ensure the connection is open and send the message
    if (tcp_client_.receive_message().empty()) {
        std::cerr << "Unable to send message. No connection established." << std::endl;
        return;
    }

    tcp_client_.send_message(message);
}

std::string TcpDestination::receive_message() {
    return tcp_client_.receive_message();
}

} // namespace palantir
