#pragma once

#include "palantir/message_source/message_source_abstract.hpp"
#include "net/udp/udp_server.hpp"

namespace palantir {

/**
 * @class UdpSource
 * 
 * @brief Implements message source functionality for receiving messages via UDP.
 *
 * UdpSource is a concrete implementation of the MessageSourceAbstract that receives
 * messages from a UDP network connection. It utilizes the UdpServer class to handle
 * low-level UDP communication, providing an interface to receive messages sent to a
 * specified port.
 */
class UdpSource : public MessageSourceAbstract {
public:
    /**
     * @brief Constructs a UdpSource object to receive messages on a specified port.
     *
     * This constructor initializes a UdpServer to listen for incoming messages on the
     * given port. The UdpServer manages the details of the network communication,
     * ensuring that messages are properly received and buffered.
     *
     * @param port The port number on which to listen for incoming UDP messages.
     */
    explicit UdpSource(int port); 
    
    ~UdpSource() override = default;

    /**
     * @brief Retrieves the next message received via UDP.
     *
     * This method checks the internal buffer of the UdpServer for any received messages,
     * returning the next available message. If no messages are currently available, it
     * may block waiting for the next message, depending on the implementation of the UdpServer.
     *
     * @return A string containing the next message received. If no messages are available,
     * it may return an empty string or block until a message is received.
     */
    std::string get_message() override;

    /**
     * @brief Checks if the source has been fully processed.
     *
     * For UdpSource, this typically indicates whether the network socket has been closed
     * or if a termination condition has been received. This method allows the caller to
     * determine when to stop processing incoming messages.
     *
     * @return true if no further messages can be received (e.g., socket closed), false otherwise.
     */
    virtual bool is_fully_processed() const override;

    /**
     * @brief Sends a response or debug message back to the sender (not typically used in production).
     *
     * This method is intended for debugging purposes to allow sending responses or acknowledgments
     * back to the sender. It utilizes the UdpServer's sending capabilities, which may be useful
     * during development or testing.
     *
     * @param message The message to send back to the sender.
     */
    // DEBUG
    void send_message(const std::string& message);

private:
    /**
     * @brief The UDP server used to receive messages.
     * 
     */
    net::UdpServer udp_source_;

    bool is_done_;
};

}       //  namespace palantir

