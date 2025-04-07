#include "palantir/messenger.hpp"
#include "palantir/command_line_args.hpp"

/**
 * The main function parses command line arguments, processes a message using encryption components,
 * and outputs a success message.
 * 
 * @param argc `argc` is the argument count, which represents the number of arguments passed to the
 * program when it is executed from the command line. It includes the name of the program itself as the
 * first argument.
 * @param argv The `argv` parameter in the `main` function is an array of C-style strings that
 * represent the command-line arguments passed to the program when it is executed. Each element in the
 * `argv` array is a null-terminated string, where `argv[0]` typically contains the name of
 */
// int main(int argc, char* argv[]) 
// {
//     palantir::CommandLineArgs cmd_args;
//     palantir::InputComponents components{};

//     cmd_args.parse_args(argc, argv, components);

//     palantir::Messenger messenger(components.encryptions_);
//     messenger.process(*components.source_, *components.destination_);

//     std::cout << "Message processed successfully.\n";

//     delete components.source_;
//     for (palantir::EncryptionAbstract* enc : components.encryptions_) {
//         delete enc;
//     }
//     delete components.destination_;

// }

int main(int argc, char* argv[]) {
    palantir::InputComponents components{};

    try {
        palantir::CommandLineArgs cmd_args;
        //palantir::InputComponents components{};

        // Parse command line arguments; this might throw if arguments are invalid
        cmd_args.parse_args(argc, argv, components);

        // Assuming Messenger might throw during setup or processing
        palantir::Messenger messenger(components.encryptions_);
        messenger.process(*components.source_, *components.destination_);

        std::cout << "Message processed successfully.\n";
    } catch (const std::exception& e) {
        // Catch any standard exceptions
        std::cerr << "An error occurred: " << e.what() << '\n';
        return 1; // Return a non-zero value to indicate failure
    } catch (...) {
        // Catch any non-standard exceptions
        std::cerr << "An unknown error occurred.\n";
        return 1;
    }

    //std::cout << "Messenger process finished" << '\n';
    // Clean up dynamically allocated resources
    delete components.source_;
    for (palantir::EncryptionAbstract* enc : components.encryptions_) {
        delete enc;
    }
    delete components.destination_;

}