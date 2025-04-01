#include "palantir/messenger.hpp"
#include <iostream>

namespace palantir {

Messenger::Messenger(const EncryptionAbstract& encryption)
: encryptions_{const_cast<EncryptionAbstract*>(&encryption)}
{
}

Messenger::Messenger(const std::vector<EncryptionAbstract*>& encryptions)
: encryptions_{encryptions}
{
}

void Messenger::process(MessageSourceAbstract& src, MessageDestinationAbstract& des) const
{
    while(!src.is_fully_processed()) {
        std::string message = src.get_message();
        for (EncryptionAbstract* encryption : encryptions_) {
            message = encryption->encode(message);
        }
        des.send_message(message);
    }
}
        
}       //  namespace palantir