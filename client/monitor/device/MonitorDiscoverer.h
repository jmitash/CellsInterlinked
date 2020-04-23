//
// Created by jacob on 4/20/2020.
//

#ifndef CELLSINTERLINKED_MONITORDISCOVERER_H
#define CELLSINTERLINKED_MONITORDISCOVERER_H

#include <vector>

#include "Monitor.h"

/**
 * Interface for discovering monitors available on the system. Implementations will be OS-dependent.
 */
class MonitorDiscoverer {
public:
    /**
     * Discovers all the available monitors on the system.
     * @return vector of monitors found on the system
     */
    [[nodiscard]] virtual std::vector<Monitor> discoverAll() const = 0;
};

#endif //CELLSINTERLINKED_MONITORDISCOVERER_H
