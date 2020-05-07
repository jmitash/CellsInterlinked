
#ifndef CELLSINTERLINKED_MONITORDISCOVERYMODULE_H
#define CELLSINTERLINKED_MONITORDISCOVERYMODULE_H

#include "application/Module.h"
#include "monitor/MonitorStateManager.h"
#include "monitor/MonitorDiscovererFactory.h"

/**
 * Responsible for discovering monitors and changes and monitors. Monitor changes will be sent as an event to be handled elsewhere (sent to the server).
 */
class MonitorDiscoveryModule : public Module {
public:
    /**
     * Creates a monitor discovery module with the given broker.
     * @param broker the broker to send monitor change messages to
     */
    explicit MonitorDiscoveryModule(Broker *const broker)
            : Module("MonitorDiscoveryModule"),
              mMonitorStateManager(broker),
              mMonitorDiscoverer(MonitorDiscovererFactory().getMonitorDiscoverer()) {}

protected:
    bool executeIteration() override;

    void yieldIteration() override;

private:
    MonitorStateManager mMonitorStateManager;
    const std::unique_ptr<MonitorDiscoverer> mMonitorDiscoverer;
};


#endif //CELLSINTERLINKED_MONITORDISCOVERYMODULE_H
