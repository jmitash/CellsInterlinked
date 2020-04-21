#include <iostream>
#include "meta/BuildInfo.h"

#include "monitor/device/MonitorDiscovererFactory.h"

int main() {
    std::cout << "Starting " << BuildInfo::projectName << " " << BuildInfo::projectVersion << " ("
              << BuildInfo::buildType << ")" << std::endl;

    MonitorDiscovererFactory factory;
    auto monitorDiscoverer = factory.getMonitorDiscoverer();

    monitorDiscoverer->discoverAll();

    return 0;
}
