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
            exit(1);
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
    }

    if (!components.source_ || components.encryptions_.empty() || !components.destination_) {
        std::cerr << "Error: Invalid component configuration\n";
        exit(1);
    }
}

} // namespace palantir