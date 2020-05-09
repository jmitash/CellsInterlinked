
#include "network/NetworkModule.h"

bool NetworkModule::executeIteration() {
    auto outgoingEvent = std::dynamic_pointer_cast<SerializableClientEvent>(mSerializableClientEventQueue->popEvent());

    if (outgoingEvent) {
        auto packet = packetConverter.serialize(outgoingEvent);
        logger.warn(packet.getPacketId());
        std::string buffer = "";
        for (const unsigned char &c : packet.getBuffer()) {
            buffer += (char) c;
        }
        spdlog::warn(buffer);
    }

    return false;
}
