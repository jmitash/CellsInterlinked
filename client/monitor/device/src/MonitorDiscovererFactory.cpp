
#include "../MonitorDiscovererFactory.h"
#include "../WindowsMonitorDiscoverer.h"

std::unique_ptr<MonitorDiscoverer> MonitorDiscovererFactory::getMonitorDiscoverer() const {
#ifdef _WIN32
    return std::unique_ptr<MonitorDiscoverer>{new WindowsMonitorDiscoverer{}};
#else
#error "Unsupported Operating System. Currently, only Windows is supported."
#endif
}