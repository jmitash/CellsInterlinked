
#include "network/SerializableClientEventPacketConverter.h"

Packet SerializableClientEventPacketConverter::serialize(const std::shared_ptr<SerializableClientEvent> &event) {
    const auto buffer = event->serialize();
    return Packet(buffer.size(), buffer);
}
