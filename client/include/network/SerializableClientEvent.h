
#ifndef CELLSINTERLINKED_SERIALIZABLECLIENTEVENT_H
#define CELLSINTERLINKED_SERIALIZABLECLIENTEVENT_H

#include "message/Event.h"
#include "network/PacketEventRegistry.h"

/**
 * An event that can be serialized in order to be sent over the network.
 */
class SerializableClientEvent : public Event {
public:
    SerializableClientEvent(const std::string &eventName,
                            unsigned short packetId,
                            int priority = 0)
            : Event(eventName, priority),
              mPacketId(packetId) {}

    /**
     * Gets the packet ID that this event converts into.
     * @return the packet ID of this event
     */
    [[nodiscard]] unsigned short getPacketId() const;

    /**
     * Serializes this event's data into a vector of bytes.
     * @return this event's data as a vector of bytes
     */
    [[nodiscard]] virtual std::vector<unsigned char> serialize() const = 0;

private:
    const unsigned short mPacketId;
};


#endif //CELLSINTERLINKED_SERIALIZABLECLIENTEVENT_H
