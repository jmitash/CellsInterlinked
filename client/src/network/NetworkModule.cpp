
#include "network/NetworkModule.h"

bool NetworkModule::executeIteration() {
    auto outgoingEvent = std::dynamic_pointer_cast<SerializableClientEvent>(mSerializableClientEventQueue->popEvent());

    if (outgoingEvent) {
        Packet packet(outgoingEvent->getPacketId(), outgoingEvent->serialize());
        logger.trace("Sending packet- ID: {}, Size: {}", packet.getPacketId(), packet.getBuffer().size());
    }

    return false;
}
