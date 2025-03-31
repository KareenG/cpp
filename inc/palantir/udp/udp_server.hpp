#include <string>
#include <netinet/in.h>

namespace palantir {

class UdpServer {
private:
    std::string ip_;
    int port_;
    int socket_id_;
    struct sockaddr_in server_addr_;

public:
    explicit UdpServer(std::string const& ip, int port);
    ~UdpServer();
    
    void start_listening();
    std::string receive();

    //DEBUG
    void send_message(const std::string& message);
};

}       //  namespace palantir