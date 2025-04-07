#include "palantir/command_line_args.hpp"

namespace palantir {

void CommandLineArgs::parse_args(int argc, char* argv[], InputComponents& components) {
    if (argc < 4) {
        std::cerr << "Usage: " << argv[0] << " <source type> <encrypt type1> <encrypt type2> ... <encrypt typeN> <dest type>\n";
        exit(1);
    }

    std::string sourceType = argv[1];
    std::string destType = argv[argc - 1];

    // Parse source type
    if (sourceType == "file") {
        std::string filename = prompt_for_input<std::string>("Enter filename for file source: ");
        components.source_ = new FileSource(filename);
    } else if (sourceType == "udp") {
        int port = prompt_for_input<int>("Enter port for UDP source: ");
        components.source_ = new UdpSource(port);
    } else if (sourceType == "console") {
        components.source_ = new ConsoleInput();
    } else if (sourceType == "tcp") {
        //components.source_ = new TcpSource(port);
        int port = prompt_for_input<int>("Enter port for TCP source: ");
        try {
            components.source_ = new TcpSource(port);
        } catch (const net::CreateSocketException& e) {
            std::cerr << "Invalid port number: " << e.what() << '\n';
            exit(EXIT_FAILURE);
        } catch (const net::BindException& e) {
            std::cerr << "Binding the port of TCP source failed: " << e.what() << '\n';
            exit(EXIT_FAILURE);
        } catch (const net::ListenException& e) {
            std::cerr << "Listening on the socket failed: " << e.what() << '\n';
            exit(EXIT_FAILURE);
        } catch (const net::AcceptException& e) {
            std::cerr << "Socket failed to accept connection: " << e.what() << '\n';
            exit(EXIT_FAILURE);
        } catch (const std::exception& e) {
            std::cerr << "General error while setting up TCP source: " << e.what() << '\n';
            exit(EXIT_FAILURE);
        }
    }
    
    // Parse encryption types
    for (int i = 2; i < argc - 1; ++i) {
        std::string encryptType = argv[i];
        EncryptionAbstract* encryption = nullptr;
        if (encryptType == "rot13") {
            encryption = new Rot13();
        } else if (encryptType == "vigenere") {
            std::string key = prompt_for_input<std::string>("Enter key for Vigenere encryption: ");
            encryption = new Vigenere(key);
        } else if (encryptType == "xor") {
            std::string key = prompt_for_input<std::string>("Enter key for XOR encryption: ");
            encryption = new XorEncryptor(key);
        } else if (encryptType == "caesar") {
            int shift = prompt_for_input<int>("Enter shift value for Caesar encryption: ");
            encryption = new Caesar(shift);
        } else if (encryptType == "atbash") {
            encryption = new Atbash();
        } else if (encryptType == "null") {
            encryption = new NullEncryption();
        } else {
            std::cerr << "Unsupported encryption type provided: " << encryptType << "\n";
            exit(EXIT_FAILURE);
        }
        components.encryptions_.push_back(encryption);
    }

    // Parse destination type
    if (destType == "file") {
        std::string filename = prompt_for_input<std::string>("Enter filename for file destination: ");
        components.destination_ = new FileDestination(filename);
    } else if (destType == "udp") {
        std::string ip = prompt_for_input<std::string>("Enter IP for UDP destination: ");
        int port = prompt_for_input<int>("Enter port for UDP destination: ");
        components.destination_ = new UdpDestination(ip, port);
    } else if (destType == "console") {
        components.destination_ = new ConsoleOutput();
    } else if (destType == "tcp") {
        std::string ip = prompt_for_input<std::string>("Enter IP for TCP destination: ");
        int port = prompt_for_input<int>("Enter port for TCP destination: ");
        //components.destination_ = new TcpDestination(ip, port);
        try {
            components.destination_ = new TcpDestination(ip, port);
            // Use components.source_ as needed, such as registering it for further operations
        } catch (const net::CreateSocketException& e) {
            std::cerr << "Create socket failed: " << e.what() << '\n';
            exit(EXIT_FAILURE);  // Exiting or you can handle it in another way based on application needs
        } catch (const net::ConnectException& e) {
            std::cerr << "Socket failed to connect to server: " << e.what() << '\n';
            exit(EXIT_FAILURE);
        } catch (const std::exception& e) {
            std::cerr << "General error while setting up TCP destination: " << e.what() << '\n';
            exit(EXIT_FAILURE);
        }
    }

    if (!components.source_ || components.encryptions_.empty() || !components.destination_) {
        std::cerr << "Error: Invalid component configuration\n";
        exit(1);
    }
}

} // namespace palantir