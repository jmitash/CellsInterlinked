
#include <fmt/format.h>
#include "remote/RemoteMonitor.h"
#include "util/SerializationUtil.h"
#include "util/DeserializationUtil.h"

std::string RemoteMonitor::getId() const {
    return mId;
}

void RemoteMonitor::setId(const std::string &id) {
    mId = id;
}

std::string RemoteMonitor::toString() const {
    auto monitorString = Monitor::toString();
    auto monitorStringNoBrackets = monitorString.substr(1, monitorString.size() - 2);

    return fmt::format(
            std::string("{{") +
            R"("Id": "{}", ")" +
            monitorStringNoBrackets +
            "}}",
            getId());
}

std::vector<unsigned char> RemoteMonitor::serialize() const {
    auto buffer = Monitor::serialize();
    SerializationUtil::convert(buffer, getId());
    return buffer;
}

void RemoteMonitor::deserialize(RemoteMonitor &monitor, std::queue<unsigned char> &buffer) {
    Monitor::deserialize(monitor, buffer);
    monitor.setId(DeserializationUtil::_string(buffer));
}
