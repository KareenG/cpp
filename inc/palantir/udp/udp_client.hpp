#include <string>
#include <netinet/in.h>

namespace palantir {
        
class UdpClient {
private:
    std::string ip_;
    int port_;
    int socket_id_;
    struct sockaddr_in server_addr_;

public:
    UdpClient(const std::string& ip, int port);
    ~UdpClient();
    void send_message(const std::string& message);

    // DEBUG
    std::string receive_message();
};
    
}       //  namespace palantir