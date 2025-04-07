#pragma once

#include <string>
#include <netinet/in.h>

namespace net {

/**
 * @class UdpServer
 * 
 * @brief Manages UDP server operations, primarily focused on receiving messages.
 *
 * UdpServer is responsible for setting up a UDP server on a specified port, receiving messages,
 * and optionally sending responses. This class abstracts the complexities of socket programming
 * and provides a streamlined interface for handling UDP communications on the server side.
 */
class UdpServer {
public:
    /**
     * @brief Constructs a UdpServer that listens on a specified port.
     *
     * This constructor sets up a UDP server to listen for incoming messages on the given port.
     * It configures the underlying socket and binds it to the specified port. If the socket 
     * setup fails, it throws a runtime_error.
     *
     * @param port The port number on which the server will listen for incoming UDP messages.
     */
    explicit UdpServer(int port); 

    /**
     * @brief Destructor.
     *
     * Ensures that the server's socket is properly closed, releasing any network resources
     * and associated connections.
     */
    ~UdpServer();
    
    /**
     * @brief Receives a message from the network.
     *
     * Listens for and receives incoming UDP messages on the configured port. This method
     * blocks until a message is received, reflecting typical server behavior in network
     * communications.
     *
     * @return A string containing the data received in the latest UDP packet.
     */
    std::string receive();

    /**
     * @brief Sends a message via UDP (used primarily for debugging).
     *
     * Sends a UDP packet containing the specified message to the sender of the last received message.
     * This method is mainly used for debugging and testing, to verify server responses or acknowledge
     * message receipt.
     *
     * @param message The message to send, formatted as a string.
     */
    //DEBUG
    void send_message(const std::string& message);

private:
    /**
     * @brief The port number on which the server listens.
     * 
     */
    //int port_;

     /**
     * @brief Identifier for the created UDP socket.
     * 
     */
    int socket_id_;
};

}       //  namespace palantir