//
// Created by jacob on 4/20/2020.
//

#ifdef _WIN32

#ifndef CELLSINTERLINKED_WINDOWSMONITORDISCOVERER_H
#define CELLSINTERLINKED_WINDOWSMONITORDISCOVERER_H

#include <windows.h>
#include "MonitorDiscoverer.h"

class WindowsMonitorDiscoverer : public MonitorDiscoverer {
public:
    std::vector<Monitor> discoverAll() const override;

private:
    std::vector<DISPLAY_DEVICE> gatherDisplayDeviceAdapters() const;

    std::vector<DISPLAY_DEVICE> gatherDisplayDeviceMonitors(const std::vector<DISPLAY_DEVICE> &displayAdapters) const;

    std::vector<HMONITOR> gatherHMonitors() const;

    static int CALLBACK monitorCallback(HMONITOR hMonitor, HDC hdcMonitor, LPRECT lprcMonitor, LPARAM dwData);

    std::vector<MONITORINFOEX> gatherMonitorInfos(const std::vector<HMONITOR> &hMonitors) const;

    std::vector<Monitor> convertMonitorInfosToMonitors(const std::vector<MONITORINFOEX> &monitorInfos) const;
};

#endif //CELLSINTERLINKED_WINDOWSMONITORDISCOVERER_H

#endif