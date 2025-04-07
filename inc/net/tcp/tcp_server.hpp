#pragma once

#include <string>
#include <netinet/in.h> // Necessary for network communication structures

namespace palantir {

/**
 * @class TcpServer
 * 
 * @brief Manages TCP server operations, primarily focused on receiving messages.
 *
 * TcpServer is responsible for setting up a TCP server on a specified port, accepting an incoming
 * connection, and optionally sending responses. This class abstracts the complexities of socket
 * programming and provides a streamlined interface for handling TCP communications.
 */
class TcpServer {
public:
    /**
     * @brief Constructs a TcpServer that listens on a specified port.
     *
     * This constructor sets up a TCP server to listen for an incoming connection on the given port.
     * It configures the underlying socket and binds it to the specified port. If the socket setup
     * fails, it prints an error message and returns.
     *
     * @param port The port number on which the server will listen for incoming connections.
     */
    explicit TcpServer(int port);

    /**
     * @brief Destructor.
     *
     * Ensures that the server's socket is properly closed, releasing any network resources
     * and associated connections.
     */
    ~TcpServer();

    /**
     * @brief Accepts the client connection.
     *
     * This method accepts an incoming client connection and returns the client socket.
     *
     * @return The client socket identifier.
     */
    int accept_client();

    /**
     * @brief Receives a message from the client.
     *
     * This method handles receiving a message from the client and returns it as a std::string.
     *
     * @param client_socket The client socket identifier.
     * @return The received message as a std::string.
     */
    std::string receive(int client_socket);

    /**
     * @brief Sends a response to the client.
     *
     * This method sends a response message to the client.
     *
     * @param client_socket The client socket identifier.
     * @param message The message to send to the client.
     */
    void send_message(int client_socket, const std::string& message);

private:
    /**
     * @brief Port number the server listens on.
     * 
     */
    int port_;     
    
     /**
     * @brief TCP socket identifier.
     * 
     */
    int socket_id_;
};

} // namespace palantir
