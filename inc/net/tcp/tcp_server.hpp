#pragma once

#include <stdexcept>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>     // For close
#include <arpa/inet.h>
#include <string>

#include "net/exceptions.hpp"
#include "net/tcp/tcp_client.hpp"

namespace net {

class TcpServer {
public:
    /**
     * @brief Constructs a TcpServer to listen for incoming connections on a specified port.
     *
     * This constructor initializes a TCP server, setting up and binding a socket to the
     * specified port to listen for incoming connections. If there is a failure in setting
     * up the socket, an error message is logged and the constructor returns.
     *
     * @param port The port number on which the server will listen for incoming connections.
     */
    explicit TcpServer(int port);

    /**
     * @brief Destructor that closes the server socket.
     *
     * Ensures that the server socket is properly closed, releasing any network resources
     * associated with this server.
     */
    ~TcpServer() noexcept;


    /**
     * @brief Accepts a new client connection.
     *
     * Waits for a new client connection attempt and, upon success, returns a TcpClient object
     * that represents the connected client. This object can then be used for further communications.
     *
     * @return TcpClient An object representing the newly connected client.
     */
    TcpClient accept_client();

private:
    /**
     * @brief Sets up the server socket.
     *
     * Configures and binds the server socket to listen on the specified port. It sets
     * the socket to non-blocking mode to allow the server to perform other tasks
     * while waiting for client connections.
     *
     * @param port The port number on which the server socket will listen.
     */
    void setup_server_socket(int port);

private:
    int server_socket_;
};

} // namespace net
