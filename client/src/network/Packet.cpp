
#include "network/Packet.h"

unsigned short Packet::getPacketId() const {
    return mPacketId;
}

std::vector<unsigned char> Packet::getBuffer() const {
    return mBuffer;
}
