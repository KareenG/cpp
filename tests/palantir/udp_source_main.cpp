#include "palantir/message_source/udp_source.hpp"
#include <iostream>

int main() {
    palantir::UdpSource udpSource(12345);  // Server listening on port 12345
    std::string received_message = udpSource.get_message();
    while (received_message.find("#EOT#") == std::string::npos) {
        std::cout << "Server received: " << received_message << '\n';
        received_message = udpSource.get_message();
    }
    return 0;
}
