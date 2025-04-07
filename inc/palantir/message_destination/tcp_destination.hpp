#pragma once

#include "palantir/message_destination/message_destination_abstract.hpp"
#include "net/tcp/tcp_client.hpp"

namespace palantir {

/**
 * @class TcpDestination
 * 
 * @brief Implements the message destination interface for sending messages via TCP.
 *
 * TcpDestination is a concrete implementation of the MessageDestinationAbstract class
 * that sends messages to a specified IP address and port using the TCP protocol. This class
 * encapsulates network communication specifics, leveraging the TcpClient class to handle
 * the low-level details of TCP socket management and data transmission.
 */
class TcpDestination : public MessageDestinationAbstract {
public:
    /**
     * @brief Constructs a TcpDestination object with a specified network address and port.
     *
     * Initializes a TCP client that will send messages to the specified IP address and port.
     * The TcpClient is set up to manage the socket lifecycle, perform message sending operations,
     * and maintain a persistent connection if required.
     *
     * @param ip The IP address of the destination.
     * @param port The port number at the destination.
     */
    explicit TcpDestination(const std::string& ip, int port);

    /**
     * @brief Destructs the TcpDestination object.
     *
     * Ensures the proper closure of the TCP connection and cleanup of resources.
     */
    ~TcpDestination() override = default;

    /**
     * @brief Sends a message over TCP to the configured destination.
     *
     * This method uses the TcpClient to send the provided message string to the destination IP and port
     * specified during the construction of this object. It ensures that the message is correctly formatted
     * and transmitted over the network.
     *
     * @param message The message to send, formatted as a string.
     */
    void send_message(const std::string& message) override;

    /**
     * @brief Receives a message from the network (for debugging purposes).
     *
     * This method is primarily used for debugging and testing to receive responses or
     * acknowledgments sent to the TCP socket managed by the TcpClient.
     *
     * @return A string containing the message received via TCP.
     */
    std::string receive_message();

private:
    /**
     * @brief The TCP client used for sending and optionally receiving messages.
     */
    net::TcpClient tcp_client_;
};

} // namespace palantir
