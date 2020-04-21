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
    std::vector<DISPLAY_DEVICE> gatherDisplayDevices() const;

    std::vector<HMONITOR> gatherHMonitors() const;

    static int CALLBACK monitorCallback(HMONITOR hMonitor, HDC hdcMonitor, LPRECT lprcMonitor, LPARAM dwData);
};

#endif //CELLSINTERLINKED_WINDOWSMONITORDISCOVERER_H

#endif