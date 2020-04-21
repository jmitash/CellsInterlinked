//
// Created by jacob on 4/21/2020.
//

#ifndef CELLSINTERLINKED_MONITORDISCOVERERFACTORY_H
#define CELLSINTERLINKED_MONITORDISCOVERERFACTORY_H

#include <memory>

#include "MonitorDiscoverer.h"

class MonitorDiscovererFactory {
public:
    std::unique_ptr<MonitorDiscoverer> getMonitorDiscoverer() const;
};


#endif //CELLSINTERLINKED_MONITORDISCOVERERFACTORY_H
