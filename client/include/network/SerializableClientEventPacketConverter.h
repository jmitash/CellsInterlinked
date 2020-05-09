
#ifndef CELLSINTERLINKED_SERIALIZABLECLIENTEVENTPACKETCONVERTER_H
#define CELLSINTERLINKED_SERIALIZABLECLIENTEVENTPACKETCONVERTER_H

#include <memory>
#include "network/Packet.h"
#include "network/SerializableClientEvent.h"

/**
 * Converts SerializableClientEvents into their corresponding Packets.
 */
class SerializableClientEventPacketConverter {
public:
    /**
     * Serializes the given event into a packet.
     * @param event the event to serialize
     * @return a packet representing the data in the event
     */
    [[nodiscard]] Packet serialize(const std::shared_ptr<SerializableClientEvent> &event);
};


#endif //CELLSINTERLINKED_SERIALIZABLECLIENTEVENTPACKETCONVERTER_H
