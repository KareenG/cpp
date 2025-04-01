#include "palantir/message_destination/udp_destination.hpp"
#include <iostream>

int main() {
    palantir::UdpDestination udpDestination("127.0.0.1", 12345);
    std::string message = "Hello from UDP client!";
    udpDestination.send_message(message);
    std::cout << "Client sent: " << message << std::endl;
    return 0;
}
