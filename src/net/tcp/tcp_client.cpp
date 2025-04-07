#include <iostream>
#include <cstring> // for memset
#include <unistd.h> // for close
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <system_error>
//#include <boost/system.hpp>

#include "net/exceptions.hpp"

#include <cassert>

#include "net/tcp/tcp_client.hpp"
#include <vector>

namespace net {

TcpClient::TcpClient(int socket)
: socket_id_{socket}
{
}
// keeeeeeeeeeeeeeeeeeeeeeeep
// TcpClient::TcpClient(const std::string& ip, int port) 
// {
//     socket_id_ = create_socket();
//     if (!attempt_connect(ip, port)) {
//         close(socket_id_);
//         socket_id_ = create_socket();
//         if (!attempt_connect(ip, port)) {
//             close(socket_id_);
//             throw SocketException(errno, "Failed to connect to server after two attempts");
//         }
//     }
// }

TcpClient::TcpClient(const std::string& ip, int port) 
{
    try {
        socket_id_ = create_socket();
    } catch (...) {
        throw;
    }
    
    try {
        attempt_connect(ip, port);
    } catch (...) {  
        throw;                
    }
}

TcpClient::~TcpClient() noexcept
{
    if (close(socket_id_) == -1) {
        std::cerr << "Failed to close socket: " << strerror(errno) << '\n';
        // Handle the error, e.g., logging to a file or error monitoring system
    }
}

int TcpClient::create_socket()
{
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        throw CreateSocketException(errno);
    }
    
    return sock;
}

void TcpClient::attempt_connect(const std::string& ip, int port) 
{
    struct sockaddr_in server_addr;
    std::fill(reinterpret_cast<char*>(&server_addr), reinterpret_cast<char*>(&server_addr) + sizeof(server_addr), 0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(ip.c_str());
    server_addr.sin_port = htons(port);

    if (connect(socket_id_, (struct sockaddr *)&server_addr, sizeof(server_addr)) != 0) {
        throw ConnectException(errno);
    }
}

/*--------------------------------------------------------------------------------------------------*/

void TcpClient::send_message(const std::string& message)
{
    size_t total = 0; // how many bytes we've sent
    size_t length = message.length();
    ssize_t result;

    while (total < length) {
        result = send(socket_id_, message.c_str() + total, length - total, 0);
        if (result < 0) {
            if (errno == EAGAIN || errno == EWOULDBLOCK) {
                // If no data is sent, try again.
                continue;
            }
            throw SendException(errno);//return handle_send_error(errno);
        }
        total += result; // increment total bytes sent
    }
}

std::string TcpClient::receive_message(size_t lenght)
{
    std::vector<char> buffer(lenght);
    std::string data;
    ssize_t n = 0;

    while (true) {
        n = recv(socket_id_, buffer.data(), buffer.size(), 0);
        if (n < 0) {
            if (errno == EAGAIN || errno == EWOULDBLOCK) {
                // If no data is received, and it's due to the buffer being temporarily unavailable, retry.
                continue;
            }
            throw ReceiveException(errno);//handle_recv_error(errno);
            //return 
        }
        if (n == 0) {
            // If n is 0, the connection has been closed by the peer.
            break;
        }
        // Append received data to the data string
        data.append(buffer.begin(), buffer.begin() + n);

        // Optionally, you can check for message completion or delimiters here if needed.
    }

    if (data.empty()) {
        return "";//{-1, "No data received, connection might be closed"};
    }
    return data;
}

} // namespace net

