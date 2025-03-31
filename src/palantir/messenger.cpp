#include "palantir/messenger.hpp"

namespace palantir {

Messenger::Messenger(EncryptionAbstract& encryption)
: encryption_{encryption}
{
}

void Messenger::process(MessageSourceAbstract& src, MessageDestinationAbstract& des) const
{
    while(!src.is_fully_processed()) {
        std::string message = src.get_message();
        std::string encrypted_message = encryption_.encode(message);
        des.send_message(encrypted_message);
    }
}
        
}       //  namespace palantir