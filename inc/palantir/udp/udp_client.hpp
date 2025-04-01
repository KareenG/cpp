#pragma once

#include <string>
#include <netinet/in.h> // Necessary for network communication structures

namespace palantir {
       
/**
 * @class UdpClient
 * 
 * @brief Manages UDP communications, sending and receiving messages over a network.
 *
 * UdpClient is responsible for setting up a UDP socket, sending messages to a specified
 * IP address and port, and optionally receiving responses. This class encapsulates the
 * details of UDP socket programming to provide a straightforward interface for network
 * message transmission.
 */
class UdpClient {
public:
    /**
     * @brief Constructs a UdpClient configured to communicate with a specific IP and port.
     *
     * Initializes the network settings for UDP communication, setting up the socket and
     * configuring it to target a specific destination. If the socket fails to create, it
     * throws a runtime_error.
     *
     * @param ip The IP address of the target destination for messages.
     * @param port The port number at the destination to which messages will be sent.
     */
    UdpClient(const std::string& ip, int port);

    /**
     * @brief Destructor.
     *
     * Ensures that the UDP socket is properly closed, releasing any associated resources.
     */
    ~UdpClient();

     /**
     * @brief Sends a message over the UDP socket to the configured destination.
     *
     * This method packages the string into a suitable format for UDP transmission and sends
     * it through the socket to the specified destination IP and port.
     *
     * @param message The message to send, formatted as a string.
     */
    void send_message(const std::string& message);

    /**
     * @brief Receives a message from the network (used primarily for debugging).
     *
     * This method listens for incoming UDP packets on the configured socket. It is intended
     * for debugging and testing, allowing for the receipt of responses or data from other
     * network nodes.
     *
     * @return A string containing the message received. If no message is available, it may
     * return an empty string or block until a message arrives, depending on socket configuration.
     */
    // DEBUG
    std::string receive_message();

private:
    /**
     * @brief IP address of the destination.
     * 
     */
    std::string ip_;

    /**
     * @brief Port number at the destination.
     * 
     */
    int port_;

    /**
     * @brief Identifier for the created UDP socket.
     * 
     */
    int socket_id_;
};
    
}       //  namespace palantir