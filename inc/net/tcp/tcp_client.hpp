#pragma once

#include <string>

namespace net {

class TcpServer; // Forward declare TcpServer

class TcpClient {
public:
    /**
     * @brief Constructs a TcpClient to communicate with a specific IP and port.
     *
     * This constructor initializes network settings for TCP communication by setting up the
     * socket and configuring its connection parameters to a specific IP and port. If the socket
     * fails to create, a std::runtime_error is thrown.
     *
     * @param ip The IP address of the target server.
     * @param port The port number on the server for communications.
     */
    explicit TcpClient(const std::string& ip, int port);

    /**
     * @brief Constructs a TcpClient using an existing socket descriptor.
     *
     * This constructor sets up the TcpClient with an existing socket descriptor, allowing
     * use of an already created and configured socket.
     *
     * @param socket The existing socket descriptor to use.
     */
    //explicit TcpClient(int socket); //friend TcpClient TcpServer::accept_client();

    /**
     * @brief Destructor that closes the TCP socket.
     *
     * Cleans up by ensuring that the TCP socket is properly closed, thereby releasing any
     * network resources associated with this client.
     */
    ~TcpClient() noexcept;

    /**
     * @brief Sends a message to the server and returns the status.
     *
     * Attempts to send a message to the server over the established connection. It returns
     * a pair where the first element is the status code (0 for success, non-zero for error)
     * and the second element is a message describing the status.
     *
     * @param message The message to be sent to the server.
     * @return std::pair<int, std::string> indicating the result of the send operation.
     */
    void send_message(const std::string& message);

    /**
     * @brief Receives a message from the server and returns the status.
     *
     * Waits for and receives a message from the server. It returns a pair where the first
     * element is the status code (0 for success, non-zero for error) and the second element
     * is the message received or an error description.
     *
     * @return std::pair<int, std::string> containing the message received and the receive status.
     */
    std::string receive_message(size_t lenght);

private:
    int create_socket();
    void attempt_connect(const std::string& ip, int port);
    std::pair<int, std::string> handle_send_error(int err);
    std::pair<int, std::string> handle_recv_error(int err);

    // Private constructor that only TcpServer can use
    /**
     * @brief Constructs a TcpClient using an existing socket descriptor.
     *
     * This constructor sets up the TcpClient with an existing socket descriptor, allowing
     * use of an already created and configured socket.
     *
     * @param socket The existing socket descriptor to use.
     */
    explicit TcpClient(int socket); // : socket_id_(socket) {}
    friend class TcpServer;// TcpServer::accept_client();
    // Declare TcpServer's accept_client function as a friend
    

private:
    int socket_id_;
};

} // namespace net
