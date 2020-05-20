
#include <gtest/gtest.h>
#include "monitor/Monitor.h"

Monitor defaultMonitor();

TEST(MonitorTest, SerializeAndDeserialize) {
    auto monitor = defaultMonitor();
    auto serializeBuffer = monitor.serialize();
    std::queue<unsigned char> deserializeBuffer;

    for (const auto &i : serializeBuffer) {
        deserializeBuffer.push(i);
    }

    auto deserializedMonitor = Monitor::deserialize(deserializeBuffer);
    EXPECT_TRUE(monitor == deserializedMonitor);
}

Monitor defaultMonitor() {
    Monitor monitor;
    monitor.setName("Name");
    monitor.setContextName("ContextName");
    monitor.setNumber((int) 0xff000000);
    monitor.setPrimary(true);
    monitor.setPixelLeft(0x00ff0000);
    monitor.setPixelTop(0x0000ff00);
    monitor.setPixelWidth(0x000000ff);
    monitor.setPixelHeight((int) 0xf0000000);
    monitor.setMillimeterWidth(999);
    monitor.setMillimeterHeight(888);
    return monitor;
}