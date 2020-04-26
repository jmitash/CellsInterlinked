
#ifdef _WIN32

#include <dshow.h>

#include "../WindowsMonitorDiscoverer.h"

std::vector<Monitor> WindowsMonitorDiscoverer::discoverAll() const {
    // TODO: will these be useful? Maybe for finding the EDID?
    auto displayAdapters = gatherDisplayDeviceAdapters();
    auto displayMonitors = gatherDisplayDeviceMonitors(displayAdapters);

    auto hMonitors = gatherMonitorHandles();
    auto monitorInfos = gatherMonitorInfos(hMonitors);
    auto monitors = mapMonitorInfosToMonitors(monitorInfos);

    return monitors;
}

std::vector<DISPLAY_DEVICE> WindowsMonitorDiscoverer::gatherDisplayDeviceAdapters() const {
    int deviceIndex = 0;
    std::vector<DISPLAY_DEVICE> displayAdapters;

    DISPLAY_DEVICE displayAdapter;
    displayAdapter.cb = sizeof(displayAdapter);

    while (EnumDisplayDevicesA(nullptr, deviceIndex++, &displayAdapter, 0)) {
        if (logger.should_log(spdlog::level::trace)) {
            logger.trace("Discovered display adapter: {}", serializeDisplayDevice(displayAdapter));
        }
        displayAdapters.push_back(displayAdapter);
    }

    return displayAdapters;
}

std::vector<DISPLAY_DEVICE>
WindowsMonitorDiscoverer::gatherDisplayDeviceMonitors(const std::vector<DISPLAY_DEVICE> &displayAdapters) const {
    std::vector<DISPLAY_DEVICE> displayMonitors;

    DISPLAY_DEVICE displayMonitor;

    for (DISPLAY_DEVICE displayAdapter : displayAdapters) {
        displayMonitor = displayAdapter;
        displayMonitor.cb = sizeof(displayMonitor);

        if (!EnumDisplayDevicesA(displayAdapter.DeviceName, 0, &displayMonitor, 0)) {
            if (logger.should_log(spdlog::level::trace)) {
                logger.trace("Display adapter did not convert to monitor: {}", serializeDisplayDevice(displayAdapter));
            }
            continue;
        }

        if (logger.should_log(spdlog::level::trace)) {
            logger.trace("Discovered display monitor from adapter: {}", serializeDisplayDevice(displayMonitor));
        }
        displayMonitors.push_back(displayMonitor);
    }

    return displayMonitors;
}

std::vector<HMONITOR> WindowsMonitorDiscoverer::gatherMonitorHandles() const {
    std::vector<HMONITOR> hMonitors;
    const auto callback = &WindowsMonitorDiscoverer::monitorCallback;
    const auto callbackParam = reinterpret_cast<LPARAM>(&hMonitors);

    if (!EnumDisplayMonitors(nullptr, nullptr, callback, callbackParam)) {
        logger.error("Error occurred while gathering monitor handles: {}", GetLastError());
    }

    return hMonitors;
}

int CALLBACK
WindowsMonitorDiscoverer::monitorCallback(HMONITOR hMonitor, HDC hdcMonitor, LPRECT lprcMonitor, LPARAM dwData) {
    auto hMonitors = reinterpret_cast<std::vector<HMONITOR> *>(dwData);
    hMonitors->push_back(hMonitor);
    return 1; // success
}

std::vector<MONITORINFOEX> WindowsMonitorDiscoverer::gatherMonitorInfos(const std::vector<HMONITOR> &hMonitors) const {
    std::vector<MONITORINFOEX> monitorInfos;

    for (const HMONITOR &hMonitor : hMonitors) {
        MONITORINFOEX monitorInfo;
        monitorInfo.cbSize = sizeof(monitorInfo);

        if (!GetMonitorInfoA(hMonitor, &monitorInfo)) {
            logger.error("Error occurred while gathering monitor infos: {}", GetLastError());
        }

        monitorInfos.push_back(monitorInfo);
    }

    return monitorInfos;
}

std::vector<Monitor>
WindowsMonitorDiscoverer::mapMonitorInfosToMonitors(const std::vector<MONITORINFOEX> &monitorInfos) const {
    std::vector<Monitor> monitors;

    for (const MONITORINFOEX &monitorInfo : monitorInfos) {
        Monitor monitor;

        monitor.setName(monitorInfo.szDevice);

        int width = monitorInfo.rcMonitor.right - monitorInfo.rcMonitor.left;
        monitor.setPixelWidth(std::abs(width));

        int height = monitorInfo.rcMonitor.bottom - monitorInfo.rcMonitor.top;
        monitor.setPixelHeight(std::abs(height));

        monitor.setPixelLeft(monitorInfo.rcMonitor.left);
        monitor.setPixelTop(monitorInfo.rcMonitor.top);

        monitor.setPrimary(monitorInfo.dwFlags & MONITORINFOF_PRIMARY);

        monitors.push_back(monitor);
    }

    return monitors;
}

std::string WindowsMonitorDiscoverer::serializeDisplayDevice(const DISPLAY_DEVICE &displayDevice) const {
    return fmt::format(R"(Name="{}", String="{}", Flags="{}", ID="{}", Key="{}")",
                       displayDevice.DeviceName,
                       displayDevice.DeviceString,
                       displayDevice.StateFlags,
                       displayDevice.DeviceID,
                       displayDevice.DeviceKey);
}

#endif