
#ifndef CELLSINTERLINKED_PACKET_H
#define CELLSINTERLINKED_PACKET_H

#include <vector>

/**
 * A packet that may be sent or received over the network.
 */
class Packet {
public:
    /**
     * Creates a packet with the given ID and buffer.
     * @param packetId the ID of this packet
     * @param buffer a buffer containing the data this packet should hold (in addition to the ID)
     */
    explicit Packet(
            unsigned short packetId,
            std::vector<unsigned char> buffer)
            : mPacketId(packetId), mBuffer(std::move(buffer)) {};

    /**
     * Gets the ID of this packet.
     * @return the ID of this packet
     */
    [[nodiscard]] unsigned short getPacketId() const;

    /**
     * Gets the data buffer of this packet.
     * @return the data buffer of this packet
     */
    [[nodiscard]] std::vector<unsigned char> getBuffer() const;

private:
    const unsigned short mPacketId;
    const std::vector<unsigned char> mBuffer;
};

#endif //CELLSINTERLINKED_PACKET_H
