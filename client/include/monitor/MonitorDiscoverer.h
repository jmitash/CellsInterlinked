
#ifndef CELLSINTERLINKED_MONITORDISCOVERER_H
#define CELLSINTERLINKED_MONITORDISCOVERER_H

#include <set>

#include "Monitor.h"

/**
 * Interface for discovering monitors available on the system. Implementations will be OS-dependent.
 */
class MonitorDiscoverer {
public:
    virtual ~MonitorDiscoverer() = default;

    /**
     * Discovers all the available monitors on the system.
     * @return set of monitors found on the system
     */
    [[nodiscard]] virtual std::set<Monitor> discoverAll() const = 0;
};

#endif //CELLSINTERLINKED_MONITORDISCOVERER_H
