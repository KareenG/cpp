#pragma once

#include "palantir/message_destination/message_destination_abstract.hpp"
#include "palantir/udp/udp_client.hpp"

namespace palantir {

/**
 * @class UdpDestination
 * 
 * @brief Implements the message destination interface for sending messages via UDP.
 *
 * UdpDestination is a concrete implementation of the MessageDestinationAbstract class
 * that sends messages to a specified IP address and port using the UDP protocol. This class
 * encapsulates network communication specifics, leveraging the UdpClient class to handle
 * the low-level details of UDP socket management and data transmission.
 */
class UdpDestination : public MessageDestinationAbstract {
public:
    /**
     * @brief Constructs a UdpDestination object with a specified network address and port.
     *
     * Initializes a UDP client that will send messages to the specified IP address and port.
     * The UdpClient is set up to manage the socket lifecycle and perform message sending operations.
     *
     * @param ip The IP address of the destination.
     * @param port The port number at the destination.
     */
    explicit UdpDestination(const std::string& ip, int port);

    ~UdpDestination() override {}

    /**
     * @brief Sends a message over UDP to the configured destination.
     *
     * This method uses the UdpClient to send the provided message string to the destination IP and port
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
     * acknowledgments sent to the UDP socket managed by the UdpClient.
     *
     * @return A string containing the message received via UDP.
     */
    // DEBUG
    std::string receive_message();

private:
    /**
     * @brief The UDP client used for sending and optionally receiving messages.
     * 
     */
    UdpClient udp_client_;
};

}       //  namespace palantir

