
#ifndef CELLSINTERLINKED_MONITORSTATEMANAGER_H
#define CELLSINTERLINKED_MONITORSTATEMANAGER_H

#include <set>
#include "logging/LogHelper.h"
#include "message/Broker.h"
#include "monitor/Monitor.h"

/**
 * Manages the monitor state for the machine.
 */
class MonitorStateManager {
public:
    /**
     * Creates a monitor state manager using the given broker.
     * @param broker the broker to use for the publishing of events
     */
    explicit MonitorStateManager(Broker *const broker) : mBroker(broker) {};

    /**
     * Tells if the given state is different from the previous state of monitors on the machine
     * @param newState the state to test if different from the previous
     * @return true if any of the given monitors are different from the previous state
     */
    [[nodiscard]] bool isDifferentState(const std::set<Monitor> &newState) const;

    /**
     * Handles the change in monitor state for the application. Fires a MonitorStateChangeEvent.
     * @param newState the new monitor state for the application
     */
    void handleStateChange(const std::set<Monitor> &newState);

private:
    std::set<Monitor> mCurrentState;
    Broker *mBroker;
    static inline spdlog::logger logger = LogHelper::logger(__FILE__);
};


#endif //CELLSINTERLINKED_MONITORSTATEMANAGER_H
