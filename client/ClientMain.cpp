#include <iostream>
#include <spdlog/spdlog.h>
#include "meta/BuildInfo.h"

#include "monitor/device/MonitorDiscovererFactory.h"

using namespace BuildInfo;

int main() {
    spdlog::info("Starting {} {} ({}) ", ::projectName, ::projectVersion, ::buildType);

    MonitorDiscovererFactory factory;
    auto monitorDiscoverer = factory.getMonitorDiscoverer();

    monitorDiscoverer->discoverAll();

    return 0;
}
