//
// Created by jacob on 4/21/2020.
//

#include "../MonitorDiscovererFactory.h"
#include "../WindowsMonitorDiscoverer.h"

std::unique_ptr<MonitorDiscoverer> MonitorDiscovererFactory::getMonitorDiscoverer() const {
#ifdef _WIN32
    return std::unique_ptr<MonitorDiscoverer>{new WindowsMonitorDiscoverer{}};
#endif
    return std::unique_ptr<MonitorDiscoverer>{nullptr};
}