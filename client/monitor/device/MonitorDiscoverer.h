//
// Created by jacob on 4/20/2020.
//

#ifndef CELLSINTERLINKED_MONITORDISCOVERER_H
#define CELLSINTERLINKED_MONITORDISCOVERER_H

#include <vector>

#include "Monitor.h"

class MonitorDiscoverer {
public:
    virtual std::vector<Monitor> discoverAll() const = 0;
};

#endif //CELLSINTERLINKED_MONITORDISCOVERER_H
