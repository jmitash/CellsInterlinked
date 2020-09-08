
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

std::string RemoteMonitor::getMachineId() const {
    return mMachineId;
}

void RemoteMonitor::setMachineId(const std::string &machineId) {
    mMachineId = machineId;
}

std::string RemoteMonitor::toString() const {
    auto monitorString = Monitor::toString();
    auto monitorStringNoBrackets = monitorString.substr(1, monitorString.size() - 2);

    return fmt::format(
            std::string("{{") +
            R"("Id": "{}", ")" +
            R"("MachineId": "{}", ")" +
            monitorStringNoBrackets +
            "}}",
            getId(),
            getMachineId());
}

std::vector<unsigned char> RemoteMonitor::serialize() const {
    auto buffer = Monitor::serialize();
    SerializationUtil::convert(buffer, getId());
    SerializationUtil::convert(buffer, getMachineId());
    return buffer;
}

void RemoteMonitor::deserialize(RemoteMonitor &monitor, std::queue<unsigned char> &buffer) {
    Monitor::deserialize(monitor, buffer);
    monitor.setId(DeserializationUtil::_string(buffer));
    monitor.setMachineId(DeserializationUtil::_string(buffer));
}
