
#ifndef CELLSINTERLINKED_REMOTEMONITOR_H
#define CELLSINTERLINKED_REMOTEMONITOR_H

#include "monitor/Monitor.h"

/**
 * Represents the state of a monitor as it would be seen remotely. This is different from a Monitor which is understood
 * as a local device. A remote monitor may represent a monitor on the local machine, but it should not be directly
 * related. The conversion from Monitor to RemoteMonitor happens server side. Remote monitors are used for configuring
 * the layout and behavior of the monitors as known to the application.
 */
class RemoteMonitor : public Monitor {
public:
    /**
     * Gets the ID for this monitor. This is a globally unique identifier assigned by the server. Monitors with
     * different IDs will be treated as different monitors entirely. If some aspect of a monitor changes (e.g.
     * resolution), it should generally keep the same ID.
     *
     * @return the ID of this monitor
     */
    [[nodiscard]] std::string getId() const;

    /**
     * Sets the ID for this monitor.
     *
     * @see RemoteMonitor::getId()
     * @param id the ID to set for this monitor
     */
    void setId(const std::string &id);

    [[nodiscard]] std::string toString() const override;

    [[nodiscard]] std::vector<unsigned char> serialize() const override;

    /**
     * Deserializes the monitor from a byte buffer.
     * @param monitor the monitor instance to deserialize into
     * @param buffer the buffer to deserialize data from
     */
    static void deserialize(RemoteMonitor &monitor, std::queue<unsigned char> &buffer);

private:
    std::string mId;
};


#endif //CELLSINTERLINKED_REMOTEMONITOR_H
