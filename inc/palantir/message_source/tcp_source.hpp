#pragma once

#include "palantir/message_source/message_source_abstract.hpp"
#include "palantir/tcp/tcp_server.hpp"

namespace palantir {

/**
 * @class TcpSource
 * 
 * @brief Implements the message source interface for receiving messages over TCP.
 *
 * TcpSource is a concrete implementation of the MessageSourceAbstract class
 * that receives messages from a client connected via TCP. This class leverages the
 * TcpServer to manage the network connection and message retrieval.
 */
class TcpSource : public MessageSourceAbstract {
public:
    /**
     * @brief Constructs a TcpSource object that listens for incoming TCP connections.
     *
     * Initializes a TCP server that listens on the specified port, accepting connections from clients.
     *
     * @param port The port number at which the server will listen for incoming connections.
     */
    explicit TcpSource(int port);

    /**
     * @brief Destructs the TcpSource object.
     *
     * Ensures the proper closure of the server's connection and cleanup of resources.
     */
    ~TcpSource() override;

    /**
     * @brief Retrieves a message from the connected client over TCP.
     *
     * This method uses the TcpServer to receive a message from the connected client.
     *
     * @return A string containing the received message from the client.
     */
    std::string get_message() override;

    /**
     * @brief Checks if the source has been fully processed.
     *
     * This method indicates whether all messages from the client have been received.
     *
     * @return true if all messages have been processed, false otherwise.
     */
    bool is_fully_processed() const override;

private:
    /**
     * @brief The TCP server used to accept and manage client connections.
     * 
     */
    TcpServer tcp_server_;
    /**
     * @brief The socket used to communicate with the connected client.
     * 
     */
    int client_socket_;
    /**
     * @brief Flag to indicate if all messages have been processed.
     * 
     */
    bool fully_processed_;
};

} // namespace palantir
