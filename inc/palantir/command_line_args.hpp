#pragma once

#include <vector>
#include <sstream> // for std::istringstream
#include <iostream>

#include "palantir/message_source/message_source_abstract.hpp"
#include "palantir/message_source/file_source.hpp"
#include "palantir/message_source/console_in.hpp"
#include "palantir/message_source/udp_source.hpp"

#include "palantir/encryption/encryption_abstract.hpp"
#include "palantir/encryption/rot13.hpp"
#include "palantir/encryption/atbash.hpp"
#include "palantir/encryption/caesar.hpp"
#include "palantir/encryption/vigenere.hpp"
#include "palantir/encryption/null_encryption.hpp"
#include "palantir/encryption/rotate.hpp"
#include "palantir/encryption/xor.hpp"

#include "palantir/message_destination/message_destination_abstract.hpp"
#include "palantir/message_destination/file_destination.hpp"
#include "palantir/message_destination/console_out.hpp"
#include "palantir/message_destination/udp_destination.hpp"

namespace palantir {

/**
 * @brief Prompts user for input and validates it, ensuring it is of the expected type.
 *
 * @param prompt The string prompt displayed to the user.
 * @return The validated user input converted to the specified type.
 */
template<typename T>
T prompt_for_input(const std::string& prompt) {
    T value;
    std::string input;
    bool valid = false;

    while (!valid) {
        std::cout << prompt;
        std::getline(std::cin, input);
        std::istringstream stream(input);

        if (stream >> value && stream.eof()) {
            valid = true;
        } else {
            std::cerr << "Invalid input, please try again.\n";
        }
    }
    return value;
}

/**
 * @struct InputComponents
 * 
 * @brief Holds pointers to configured components for message processing: source, encryption, and destination.
 */
struct InputComponents {
    MessageSourceAbstract* source_ = nullptr;
    std::vector<EncryptionAbstract*> encryptions_;
    MessageDestinationAbstract* destination_ = nullptr;
};

/**
 * @class CommandLineArgs
 * 
 * @brief Parses command-line arguments and sets up message processing components based on the user input.
 */
class CommandLineArgs {
public:
    /**
     * @brief Parses the command-line arguments to configure the input, encryption, and output components.
     *
     * @param argc The number of command-line arguments.
     * @param argv The array of command-line argument strings.
     * @param components The structure holding pointers to the configured components.
     */
    void parse_args(int argc, char* argv[], InputComponents& components);
};

} // namespace palantir
