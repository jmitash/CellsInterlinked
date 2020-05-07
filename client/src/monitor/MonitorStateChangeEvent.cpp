
#include "monitor/MonitorStateChangeEvent.h"

std::set<Monitor> MonitorStateChangeEvent::getNewMonitors() const {
    return mMonitors;
}
