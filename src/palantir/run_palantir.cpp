#include "palantir/messenger.hpp"
#include "palantir/command_line_args.hpp"

int main(int argc, char* argv[]) 
{
    palantir::CommandLineArgs cmd_args;
    palantir::InputComponents components{};

    cmd_args.parse_args(argc, argv, components);

    palantir::Messenger messenger(components.encryptions_);
    messenger.process(*components.source_, *components.destination_);

    std::cout << "Message processed successfully.\n";

    delete components.source_;
    for (palantir::EncryptionAbstract* enc : components.encryptions_) {
        delete enc;
    }
    delete components.destination_;

}
