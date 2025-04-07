#pragma once

// #include <iostream>
// #include <system_error>
// #include <string>
// #include <cerrno>
// #include <cstring>
// #include <sys/socket.h>
// #include <unistd.h>
// #include <stdexcept>

#include <system_error>
#include <string>
#include <arpa/inet.h>

namespace net {

// // Using std::system_error to include error codes along with messages
// class SocketException : public std::system_error {
// public:
//     SocketException(int error_code, const std::string& message)
//     : std::system_error(error_code, std::system_category(), message)
//     {
//     }
// };

// class CreateSocketException : public SocketException {
// public:
//     CreateSocketException(int error_code, const std::string& msg)
//     : SocketException(error_code, "Invalid argument: " + msg) 
//     {
//     }
// };

// class InvalidArgument : public SocketException {
// public:
//     InvalidArgument(int error_code, const std::string& msg)
//     : SocketException(error_code, "Invalid argument: " + msg) 
//     {
//     }
// };

// class SendException : public SocketException {  //std::system_error
// public:
//     SendException(int error_code, const std::string& msg)
//     //: std::system_error(error_code, std::system_category(), "Send failed: " + msg)
//     : SocketException(error_code, "Send failed: " + msg)
//     {
//     }
// };

// class ReceiveException : public SocketException {  //std::system_error
// public:
//     ReceiveException(int error_code, const std::string& msg)
//     //: std::system_error(error_code, std::system_category(), "Receive failed: " + msg)
//     : SocketException(error_code, "Receive failed: " + msg)
//     {
//     }
// };

// class BindException : public SocketException {  //std::system_error
// public:
//     BindException(int error_code, const std::string& msg)
//     //: std::system_error(error_code, std::system_category(), "Bind failed: " + msg)
//     : SocketException(error_code, "Bind failed: " + msg)
//     {
//     }
// };

// class ListenException : public SocketException {  //std::system_error
// public:
//     ListenException(int error_code, const std::string& msg)
//     //: std::system_error(error_code, std::system_category(), "Listen failed: " + msg)
//     : SocketException(error_code, "Listen failed: " + msg)
//     {
//     }
// };

// class AcceptException : public SocketException {  //std::system_error
// public:
//     AcceptException(int error_code, const std::string& msg)
//     : SocketException(error_code, "Client accept failed: " + msg) 
//     //: std::system_error(error_code, std::system_category(), "Client accept failed: " + msg) 
//     {
//     }
// };

// class ConnectException : public SocketException {  // New exception class for connect errors
// public:
//     ConnectException(int error_code, const std::string& msg)
//     : SocketException(error_code, "Connect failed: " + msg)
//     {
//     }
// };

// class CloseException : public SocketException {  // Exception class for close errors
// public:
//     CloseException(int error_code, const std::string& msg)
//     : SocketException(error_code, "Close failed: " + msg)
//     {
//     }
// };

// bool is_valid_port(int port)
// {
//     return (0 <= port) || (port <= 65535);
// }

// bool is_valid_ip(const std::string& ip) {
//     struct sockaddr_in sa{};
//     struct sockaddr_in6 sa6{};
//     if (inet_pton(AF_INET, ip.c_str(), &(sa.sin_addr)) == 1) {
//         return true;
//     }
//     if (inet_pton(AF_INET6, ip.c_str(), &(sa6.sin6_addr)) == 1) {
//         return true;
//     }
//     return false;
// }

// enum class AcceptStatus {
//     Success,
//     Fail,
//     TryAgain  // Indicates to try the accept again later
// };

// // Base class for all socket-related exceptions
// class SocketException : public std::system_error {
// public:
//     SocketException(int error_code, const std::string& message)
//     : std::system_error(error_code, std::system_category(), message)
//     {
//     }
// };

// // Exception class for permission-related errors
// class SocketPermissionException : public SocketException {
// public:
//     SocketPermissionException(int error_code, const std::string& msg)
//     : SocketException(error_code, "Permission denied: " + msg)
//     {
//     }
// };

// // Exception class for invalid argument errors
// class InvalidSocketArgument : public SocketException {
// public:
//     InvalidSocketArgument(int error_code, const std::string& msg)
//     : SocketException(error_code, "Invalid argument: " + msg)
//     {
//     }
// };

// // Exception class for resource limit errors
// class SocketResourceLimitException : public SocketException {
// public:
//     SocketResourceLimitException(int error_code, const std::string& msg)
//     : SocketException(error_code, "Resource limit exceeded: " + msg)
//     {
//     }
// };

// // Exception class for insufficient memory errors
// class InsufficientMemoryException : public SocketException {
// public:
//     InsufficientMemoryException(int error_code, const std::string& msg)
//     : SocketException(error_code, "Insufficient memory: " + msg)
//     {
//     }
// };

// Base class for all socket-related exceptions
class SocketException : public std::system_error {
public:
    SocketException(int error_code, const std::string& message)
    : std::system_error(error_code, std::system_category(), message) {}
};

class CreateSocketException : public SocketException {
public:
    CreateSocketException(int error_code)
    : SocketException(error_code, "Socket creation failed") {}
};

class BindException : public SocketException {
public:
    BindException(int error_code)
    : SocketException(error_code, "Bind failed") {}
};

class ListenException : public SocketException {
public:
    ListenException(int error_code)
    : SocketException(error_code, "Listen failed") {}
};

class AcceptException : public SocketException {
public:
    AcceptException(int error_code)
    : SocketException(error_code, "Client accept failed") {}
};

class ConnectException : public SocketException {
public:
    ConnectException(int error_code)
    : SocketException(error_code, "Connection failed") {}
};

class SendException : public SocketException {
public:
    SendException(int error_code)
    : SocketException(error_code, "Send failed") {}
};

class ReceiveException : public SocketException {
public:
    ReceiveException(int error_code)
    : SocketException(error_code, "Receive failed") {}
};
}       // namespace net



