#include "palantir/messenger.hpp"
#include <iostream>

namespace palantir {

Messenger::Messenger(EncryptionAbstract const& encryption)
: encryptions_{const_cast<EncryptionAbstract*>(&encryption)}
{
}

Messenger::Messenger(std::vector<EncryptionAbstract*> const& encryptions)
: encryptions_{encryptions}
{
}

// void Messenger::process(MessageSourceAbstract& src, MessageDestinationAbstract& des) const
// {
//     while(!src.is_fully_processed()) {
//         std::string message = src.get_message();
//         for (EncryptionAbstract* encryption : encryptions_) {
//             message = encryption->encode(message);
//         }
//         des.send_message(message);
//     }
// }

void Messenger::process(MessageSourceAbstract& src, MessageDestinationAbstract& des) const 
{
    while(!src.is_fully_processed()) {
        try {
            std::string message = src.get_message();  // Receive message

            // Apply all encryptions
            for (EncryptionAbstract* encryption : encryptions_) {
                message = encryption->encode(message);
            }

            des.send_message(message);  // Send message
        } //catch (const net::SocketException& e) {
            // Handle specific network-related errors
            //std::cerr << "Network error: " << e.what() << '\n';
        // } 
        catch (const std::exception& e) {
            // Handle any other standard exceptions
            //std::cerr << "Error during message processing: " << e.what() << '\n';
            throw;
        }
    }
}

        
}       //  namespace palantir