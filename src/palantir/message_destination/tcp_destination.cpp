#include <iostream>

#include "palantir/message_destination/tcp_destination.hpp"
#include "net/exceptions.hpp"

namespace palantir {

// TcpDestination::TcpDestination(const std::string& ip, int port)
// : tcp_client_(ip, port)
// {
// }

TcpDestination::TcpDestination(const std::string& ip, int port)
try
: tcp_client_(ip, port) 
{
    // Additional initialization can go here if necessary
} catch (const net::CreateSocketException& e) {
    // Handle send errors specifically
    //std::cerr << "Create socket failed: " << e.what() << '\n';
    throw;
} catch (const net::ConnectException& e) {
    //std::cerr << "Socket failed to connect to server: " << e.what() << '\n';
    throw;
    //throw; // Rethrow to signal that TcpDestination could not be properly initialized
}catch (const std::exception& e) {
    //std::cerr << "Unexpected error occured: " << e.what() << '\n';
    throw; // Rethrow to signal that TcpDestination could not be properly initialized
}

void TcpDestination::send_message(const std::string& message) 
{
    try {
        tcp_client_.send_message(message);
        //std::cout << "Message sent successfully\n";
    } catch (const net::SendException& e) {
        // Handle send errors specifically
        //std::cerr << "Error sending message: " << e.what() << '\n';
    } catch (const std::exception& e) {
        // Handle other possible exceptions
        //std::cerr << "General error when sending message: " << e.what() << '\n';
    }
}

std::string TcpDestination::receive_message() 
{
    try {
        // Attempt to receive a message from the TcpClient
        std::string message = tcp_client_.receive_message(1024);
        return message;
    } catch (const net::ReceiveException& e) {
        // Handle specific receive errors
        //std::cerr << "Receive error: " << e.what() << '\n';
        return ""; // Return an empty string indicating a failure specific to reception issues
    } catch (const std::exception& e) {
        // Handle any other exceptions
        //std::cerr << "Error receiving message: " << e.what() << '\n';
        return ""; // Return an empty string or alternatively, you might want to rethrow the exception or handle it differently
    }
}

} // namespace palantir
