
#ifndef CELLSINTERLINKED_MONITORSTATECHANGEEVENT_H
#define CELLSINTERLINKED_MONITORSTATECHANGEEVENT_H

#include <set>
#include <utility>
#include "message/Event.h"
#include "monitor/Monitor.h"

/**
 * An event representing a change of/in the monitors that were detected previously detected on this device. This is also fired the first monitors are detected.
 */
class MonitorStateChangeEvent : public Event {
public:
    /**
     * Creates a monitor state change event with the given monitors as the new state.
     * @param newMonitors the new monitor state of the machine
     */
    explicit MonitorStateChangeEvent(std::set<Monitor> newMonitors)
            : Event("MonitorStateChangeEvent"), mMonitors(std::move(newMonitors)) {};

    /**
     * Gets the new monitor state of the machine.
     * @return the changed version of the monitors on the machine
     */
    [[nodiscard]] std::set<Monitor> getNewMonitors() const;

private:
    const std::set<Monitor> mMonitors;
};


#endif //CELLSINTERLINKED_MONITORSTATECHANGEEVENT_H
