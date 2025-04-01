#include "palantir/messenger.hpp"

namespace palantir {

Messenger::Messenger(const std::vector<EncryptionAbstract*>& encryptions)
: encryptions_{encryptions}
{
}

void Messenger::process(MessageSourceAbstract& src, MessageDestinationAbstract& des) const
{
    while(!src.is_fully_processed()) {
        std::string message = src.get_message();
        std::string encrypted_message;
        for (EncryptionAbstract* encryption : encryptions_) {
            encrypted_message = encryption->encode(message);
        }
        des.send_message(encrypted_message);
    }
}
        
}       //  namespace palantir