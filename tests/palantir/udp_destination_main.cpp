#include "palantir/message_destination/udp_destination.hpp"
#include <iostream>

int main() {
    palantir::UdpDestination udpDestination("127.0.0.1", 12345);
    std::string message;
    while(true) {
        std::cin >> message;
        udpDestination.send_message(message);
        std::cout << "Client sent: " << message << '\n';
    }
    
    return 0;
}
