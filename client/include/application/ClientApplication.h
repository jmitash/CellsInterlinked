
#ifndef CELLSINTERLINKED_CLIENTAPPLICATION_H
#define CELLSINTERLINKED_CLIENTAPPLICATION_H

#include <vector>
#include "logging/LogHelper.h"
#include "application/Module.h"
#include "monitor/MonitorDiscoveryModule.h"
#include "mouse/MouseCaptureModule.h"
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
              mNetworkModule(&broker),
              mMouseCaptureModule(&broker) {
        mAllModules.push_back(&mNetworkModule);
        mAllModules.push_back(&mMonitorDiscoveryModule);
        mAllModules.push_back(&mMouseCaptureModule);
    }

    /**
     * Runs the application.
     */
    void run();

private:
    Broker broker;
    MonitorDiscoveryModule mMonitorDiscoveryModule;
    MouseCaptureModule mMouseCaptureModule;
    NetworkModule mNetworkModule;
    std::vector<Module *> mAllModules;
    inline static auto logger = LogHelper::logger(__FILE__);
};


#endif //CELLSINTERLINKED_CLIENTAPPLICATION_H
