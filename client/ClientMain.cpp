
#include <spdlog/spdlog.h>

#include "meta/BuildInfo.h"
#include "monitor/device/MonitorDiscovererFactory.h"

int main() {
    spdlog::info("Starting {} {} ({})", BuildInfo::projectName, BuildInfo::projectVersion, BuildInfo::buildType);

    MonitorDiscovererFactory factory;
    auto monitorDiscoverer = factory.getMonitorDiscoverer();

    monitorDiscoverer->discoverAll();

    return 0;
}
