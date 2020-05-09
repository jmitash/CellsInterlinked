
#ifndef CELLSINTERLINKED_CLIENTAPPLICATION_H
#define CELLSINTERLINKED_CLIENTAPPLICATION_H

#include <vector>
#include "logging/LogHelper.h"
#include "application/Module.h"
#include "monitor/MonitorDiscoveryModule.h"
#include "network/NetworkModule.h"

/**
 * The client application. Serves as a starting point for initializing and running the application.
 */
class ClientApplication {
public:
    /**
     * Creates a client application, initializing (but not yet running) each of the modules.
     */
    ClientApplication()
            : mMonitorDiscoveryModule(&broker),
              mNetworkModule(&broker) {
        mAllModules.push_back(&mNetworkModule);
        mAllModules.push_back(&mMonitorDiscoveryModule);
    }

    /**
     * Runs the application.
     */
    void run();

private:
    Broker broker;
    MonitorDiscoveryModule mMonitorDiscoveryModule;
    NetworkModule mNetworkModule;
    std::vector<Module *> mAllModules;
    inline static auto logger = LogHelper::logger(__FILE__);
};


#endif //CELLSINTERLINKED_CLIENTAPPLICATION_H
