
#ifndef CELLSINTERLINKED_MONITORDISCOVERERFACTORY_H
#define CELLSINTERLINKED_MONITORDISCOVERERFACTORY_H

#include <memory>

#include "MonitorDiscoverer.h"

/**
 * Factory to provide an instance of a MonitorDiscoverer. This factory is meant to hide the OS-specific implementation of monitor discoverers.
 */
class MonitorDiscovererFactory {
public:
    /**
     * Creates a monitor discoverer supported by the current operating system and returns a pointer to it.
     * @return a pointer to a new monitor discoverer instance
     */
    [[nodiscard]] std::unique_ptr<MonitorDiscoverer> getMonitorDiscoverer() const;
};


#endif //CELLSINTERLINKED_MONITORDISCOVERERFACTORY_H
