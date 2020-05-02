
#include "monitor/MonitorDiscovererFactory.h"
#include "monitor/WindowsMonitorDiscoverer.h"
#include "meta/BuildInfo.h"

std::unique_ptr<MonitorDiscoverer> MonitorDiscovererFactory::getMonitorDiscoverer() const {
    BuildInfo::assertSupportedPlatform();

    if constexpr (BuildInfo::isWindows()) {
        return std::make_unique<WindowsMonitorDiscoverer>();
    } else {
        return std::unique_ptr<MonitorDiscoverer>(nullptr);
    }
}