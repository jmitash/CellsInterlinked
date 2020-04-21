//
// Created by jacob on 4/20/2020.
//

#ifdef _WIN32

#include <iostream>
#include <system_error>

#include "../WindowsMonitorDiscoverer.h"

std::vector<Monitor> WindowsMonitorDiscoverer::discoverAll() const {
    std::vector<HMONITOR> hMonitors = gatherHMonitors();

    return std::vector<Monitor>{};
}

std::vector<DISPLAY_DEVICE> WindowsMonitorDiscoverer::gatherDisplayDevices() const {
    int deviceIndex = 0;
    std::vector<DISPLAY_DEVICE> displayDevices;

    DISPLAY_DEVICE displayDevice;
    displayDevice.cb = sizeof(displayDevice);

    while (EnumDisplayDevicesA(nullptr, deviceIndex++, &displayDevice, 0)) {
        displayDevices.push_back(displayDevice);
    }

    return displayDevices;
}

std::vector<HMONITOR> WindowsMonitorDiscoverer::gatherHMonitors() const {
    std::vector<HMONITOR> hMonitors;
    const auto callback = &WindowsMonitorDiscoverer::monitorCallback;
    const auto callbackParam = reinterpret_cast<LPARAM>(&hMonitors);

    if (!EnumDisplayMonitors(nullptr, nullptr, callback, callbackParam)) {
        throw std::system_error{-1, std::generic_category()};
    }

    return hMonitors;
}

int CALLBACK
WindowsMonitorDiscoverer::monitorCallback(HMONITOR hMonitor, HDC hdcMonitor, LPRECT lprcMonitor, LPARAM dwData) {
    auto hMonitors = reinterpret_cast<std::vector<HMONITOR> *>(dwData);
    hMonitors->push_back(hMonitor);
    return 1; // success
}

#endif