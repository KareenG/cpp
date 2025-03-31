#pragma once

#include "palantir/encryption/encryption_abstract.hpp"
#include "palantir/message_source/message_source_abstract.hpp"
#include "palantir/message_destination/message_destination_abstract.hpp"

namespace palantir {

class Messenger {
private:
    EncryptionAbstract& encryption_;

public:
    Messenger(EncryptionAbstract& encryption);

    ~Messenger() = default;     //  Messenger does not own the EncryptionAbstract

    void process(MessageSourceAbstract& src, MessageDestinationAbstract& des) const;
};
    
}       //  namespace palantir

