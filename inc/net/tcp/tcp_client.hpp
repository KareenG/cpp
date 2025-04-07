#pragma once

#include <string>
#include <netinet/in.h> // Necessary for network communication structures

namespace palantir {

class TcpClient {
public:
    /**
     * @brief Constructs a TcpClient configured to communicate with a specific IP and port.
     *
     * Initializes the network settings for TCP communication, setting up the socket and
     * configuring it to target a specific destination. If the socket fails to create, it
     * throws a runtime_error.
     *
     * @param ip The IP address of the target destination for messages.
     * @param port The port number at the destination to which messages will be sent.
     */
    TcpClient(const std::string& ip, int port);

    /**
     * @brief Destructor.
     *
     * Ensures that the TCP socket is properly closed, releasing any associated resources.
     */
    ~TcpClient();

    /**
     * @brief Connects to the server.
     *
     * This method establishes a connection to the server at the given IP address and port.
     *
     * @return true if the connection was successful, false otherwise.
     */
    bool connect_to_server();

    /**
     * @brief Closes the client connection.
     */
    void close_connection();

    /**
     * @brief Sends a message to the server.
     *
     * This method sends a message to the server over the established connection.
     *
     * @param message The message to send.
     */
    void send_message(const std::string& message);

    /**
     * @brief Receives a message from the server.
     *
     * This method receives a message from the server.
     *
     * @return A string containing the message received from the server.
     */
    std::string receive_message();

private:
    std::string ip_;
    int port_;
    int socket_id_;
    bool connected_;
};

} // namespace palantir
