
#include "monitor/MonitorStateChangeEvent.h"
#include "util/SerializationUtil.h"

std::set<Monitor> MonitorStateChangeEvent::getNewMonitors() const {
    return mMonitors;
}

std::vector<unsigned char> MonitorStateChangeEvent::serialize() const {
    std::vector<unsigned char> buffer;
    SerializationUtil::convert(buffer, mMonitors.begin(), mMonitors.end(), [](const Monitor &monitor) {
        return monitor.serialize();
    });
    return buffer;
}
