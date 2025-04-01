#pragma once

#include <vector>

#include "palantir/encryption/encryption_abstract.hpp"
#include "palantir/message_source/message_source_abstract.hpp"
#include "palantir/message_destination/message_destination_abstract.hpp"

namespace palantir {

/**
 * @class Messenger
 * 
 * @brief Facilitates the encryption and transmission of messages between sources and destinations.
 *
 * The Messenger class uses a series of encryption strategies provided upon construction
 * to process messages from a source to a destination. It allows for multiple layers of
 * encryption by iterating through a list of EncryptionAbstract pointers.
 */
class Messenger {
public:
    /**
     * @brief Constructs a Messenger with a single encryption.
     *
     * This constructor initializes the messenger with a single EncryptionAbstract reference,
     * and adds it to the list of encryptions.
     *
     * @param encryption A reference to an EncryptionAbstract representing the single encryption layer to apply to messages.
     */
    explicit Messenger(const EncryptionAbstract& encryption);

    /**
     * @brief Constructs a Messenger with a list of encryptions.
     *
     * This constructor initializes the messenger with a vector of pointers to EncryptionAbstract,
     * allowing for the application of multiple encryption strategies to the messages processed.
     *
     * @param encryptions A vector of pointers to EncryptionAbstract representing the sequence
     *                    of encryption layers to apply to messages.
     */
    explicit Messenger(const std::vector<EncryptionAbstract*>& encryptions);

    ~Messenger() = default;

    /**
     * @brief Processes messages from a source to a destination using configured encryptions.
     *
     * This method retrieves messages from the specified source, applies each encryption in the 
     * sequence defined at construction, and forwards the resulting message to the designated 
     * destination.
     *
     * @param src Reference to an implementation of MessageSourceAbstract from which messages are read.
     * @param des Reference to an implementation of MessageDestinationAbstract to which messages are sent.
     */
    void process(MessageSourceAbstract& src, MessageDestinationAbstract& des) const;

private:
    /**
     * @brief Stores the sequence of encryption strategies.
     * 
     */
    std::vector<EncryptionAbstract*> encryptions_;
};
    
}       //  namespace palantir

