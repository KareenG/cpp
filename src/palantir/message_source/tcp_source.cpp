#include <iostream>
#include <unistd.h>

#include "net/exceptions.hpp"
#include "palantir/message_source/tcp_source.hpp"
#include "net/tcp/tcp_client.hpp"

namespace palantir {

TcpSource::TcpSource(int port)
try 
: tcp_server_(port)
, fully_processed_(false) {
} catch (const net::CreateSocketException& e) {
    //std::cerr << "Create socket failed: " << e.what() << '\n';
    throw;
} catch (const net::BindException& e) {
    //std::cerr << "Socket failed to bind to the giving port: " << e.what() << '\n';
    throw;
} catch (const net::ListenException& e) {
    //std::cerr << "Socket failed to listen: " << e.what() << '\n';
    throw;
} catch (const net::AcceptException& e) {
    //std::cerr << "Socket failed to accept connection: " << e.what() << '\n';
    throw;
} catch (...) {
    //std::cerr << "Unexpected error occured: " << '\n';
    throw;
}

std::string TcpSource::get_message() 
{
    net::TcpClient client = tcp_server_.accept_client();
    try {
        std::string message = client.receive_message(1024);
        size_t delimiter_pos = message.find_first_of("/n."); //.find("./n"); //'\x04'
        if (delimiter_pos != std::string::npos) {
            message = message.substr(0, delimiter_pos);
            fully_processed_ = true;
        } 
        return message;

    } catch (const net::ReceiveException& e) {
        //std::cerr << "Receive error: " << e.what() << '\n';
        return "";
    } catch (const std::exception& e) {
        //std::cerr << "Error receiving message: " << e.what() << '\n';
        return "";
    }
}

bool TcpSource::is_fully_processed() const 
{
    return fully_processed_;
}

} // namespace palantir
