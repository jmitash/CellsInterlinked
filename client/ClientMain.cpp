
#include "../common/logging/LogHelper.h"
#include "meta/BuildInfo.h"
#include "monitor/device/MonitorDiscovererFactory.h"

int main() {
    spdlog::logger logger = LogHelper::logger(__FILE__);
    logger.info("Starting {} {} ({})", BuildInfo::projectName, BuildInfo::projectVersion, BuildInfo::buildType);

    MonitorDiscovererFactory factory;
    auto monitorDiscoverer = factory.getMonitorDiscoverer();

    monitorDiscoverer->discoverAll();

    return 0;
}
