
#ifndef CELLSINTERLINKED_WINDOWSMONITORDISCOVERER_H
#define CELLSINTERLINKED_WINDOWSMONITORDISCOVERER_H

#include "MonitorDiscoverer.h"
#include "logging/LogHelper.h"

#ifdef _WIN32

#include <windows.h>

/**
 * Monitor discoverer implementation for Windows.
 */
class WindowsMonitorDiscoverer : public MonitorDiscoverer {
public:
    [[nodiscard]] std::vector<Monitor> discoverAll() const override;

private:
    /**
     * Gathers all the display adapters on the system.
     * @return a vector of display devices representing display adapters
     */
    [[nodiscard]] std::vector<DISPLAY_DEVICE> gatherDisplayDeviceAdapters() const;

    /**
     * Gathers all the display monitors on the system. These will be the display adapters that are tied to a monitor. The display device should contain the monitor name as the @code DISPLAY_DEVICE.DeviceString @endcode but this may often be something generic such as "Generic PnP Monitor". If there is not a monitor associated with the display adapter, the resulting monitor will have all fields zeroed except for size.
     * @param displayAdapters the display adapters to find associated monitors of
     * @return a vector of display devices representing the monitors associated with the given display adapters
     */
    [[nodiscard]] std::vector<DISPLAY_DEVICE>
    gatherDisplayDeviceMonitors(const std::vector<DISPLAY_DEVICE> &displayAdapters) const;

    /**
     * Gathers all handles to monitors on the system.
     * @return a vector of monitor handles on the system
     */
    [[nodiscard]] std::vector<HMONITOR> gatherMonitorHandles() const;

    /**
     * A callback function that will be invoked when a monitor handle is discovered.
     * @param hMonitor the handle to the discovered monitor
     * @param hdcMonitor a handle to the device context for the monitor
     * @param lprcMonitor a rectangle representing the area this monitor covers (virtual-screen coordinates)
     * @param dwData passthrough data from the caller that initiated the enumeration process (in our case, a pointer to a vector of monitor handlers to add the handle to)
     * @return non-zero to continue enumeration, zero to stop (in our case, always 1)
     */
    static int CALLBACK monitorCallback(HMONITOR hMonitor, HDC hdcMonitor, LPRECT lprcMonitor, LPARAM dwData);

    /**
     * Gathers monitor infos corresponding to the passed in monitor handles.
     * @param hMonitors the monitor handles to find infos for
     * @return vector of monitor infos
     */
    [[nodiscard]] std::vector<MONITORINFOEX> gatherMonitorInfos(const std::vector<HMONITOR> &hMonitors) const;

    /**
     * Maps the given monitor infos into Monitors, populating as much information on the monitor as possible.
     * @param monitorInfos the monitor infos to create Monitors out of
     * @return a vector of Monitors corresponding to the given monitor infos
     */
    [[nodiscard]] std::vector<Monitor> mapMonitorInfosToMonitors(const std::vector<MONITORINFOEX> &monitorInfos) const;

    /**
     * Converts a display device to a human readable string.
     * @param displayDevice the display device to convert
     * @return string form of the display device
     */
    [[nodiscard]] std::string toString(const DISPLAY_DEVICE &displayDevice) const;

    inline static auto logger = LogHelper::logger(__FILE__);
};

#else // not _WIN32

class WindowsMonitorDiscoverer : public MonitorDiscoverer {
public:
    [[nodiscard]] std::vector<Monitor> discoverAll() const override { 
        return std::vector<Monitor>();
    }
};

#endif // _WIN32
#endif //CELLSINTERLINKED_WINDOWSMONITORDISCOVERER_H

