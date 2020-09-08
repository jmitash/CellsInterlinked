
#include <gtest/gtest.h>
#include "remote/RemoteMonitor.h"

TEST(RemoteMonitorTest, SerializeAndDeserialize) {
    RemoteMonitor monitor;
    monitor.setName("name");
    monitor.setId("id");
    monitor.setMachineId("machineId");

    auto serializeBuffer = monitor.serialize();
    std::queue<unsigned char> deserializeBuffer;

    for (const auto &i : serializeBuffer) {
        deserializeBuffer.push(i);
    }

    RemoteMonitor deserialized;
    RemoteMonitor::deserialize(deserialized, deserializeBuffer);

    EXPECT_EQ("name", deserialized.getName());
    EXPECT_EQ("id", deserialized.getId());
    EXPECT_EQ("machineId", deserialized.getMachineId());
}