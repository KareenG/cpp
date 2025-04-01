#include <iostream>
#include <fstream>

#include "palantir/message_source/udp_source.hpp"

namespace palantir {

UdpSource::UdpSource(int port) 
: udp_source_{port}
{
}

std::string UdpSource::get_message() 
{
    return udp_source_.receive();
}

bool UdpSource::is_fully_processed() const 
{
    std::cout << "Select an option:\n";
    std::cout << "1. Wait for a message\n";
    std::cout << "2. Stop\n";
    int choice;
    std::cin >> choice;

    if (choice == 2) {
        return true;
    } else {
        std::cout << "Continuing to wait for messages...\n";
    }
    return false;
}

//DEBUG
void UdpSource::send_message(const std::string& message) 
{
    std::ofstream file("test_udp_source.txt", std::ios::app); // Open in append mode
    if (file.is_open()) {
        file << message << '\n';
        file.close();
    } else {
        std::cerr << "Failed to open file for writing." << '\n';
    }

    udp_source_.send_message(message);
}

};