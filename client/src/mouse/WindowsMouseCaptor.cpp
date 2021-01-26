
#include "mouse/WindowsMouseCaptor.h"

#ifdef _WIN32

#include <memory>
#include <hidusage.h>

typedef WindowsMouseCaptor::WindowsMouse WindowsMouse;

void WindowsMouseCaptor::run() {
    std::vector<WindowsMouse> mice = getWindowsMice();
    populateWindowsMice(mice);

    HWND hWindow = createCaptorWindow();

    registerMiceInputDevices(mice, hWindow);

    MSG msg;
    while (GetMessage(&msg, hWindow, 0, 0)) {
        handleMessage(msg);
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    logger.error("Mouse Captor Window Message Loop Ended");
}

std::vector<WindowsMouse> WindowsMouseCaptor::getWindowsMice() {
    const size_t ridlSize = sizeof(RAWINPUTDEVICELIST);

    // get the device count
    UINT devicesCount;
    if (!GetRawInputDeviceList(nullptr, &devicesCount, ridlSize)) {
        // TODO: error
    }
    logger.trace("Discovered {} devices", devicesCount);

    // get the actual devices
    auto devices = std::unique_ptr<RAWINPUTDEVICELIST[]>(new RAWINPUTDEVICELIST[devicesCount]);
    devicesCount = GetRawInputDeviceList(devices.get(), &devicesCount, ridlSize);
    if (devicesCount == -1) {
        // TODO: error
    }

    // build the mice based on handle
    std::vector<WindowsMouse> mice;
    for (int i = 0; i < devicesCount; i++) {
        auto deviceEntry = devices[i];

        if (deviceEntry.dwType == RIM_TYPEMOUSE) {
            WindowsMouse windowsMouse;
            windowsMouse.handle = deviceEntry.hDevice;
            mice.push_back(windowsMouse);
        } else {
            logger.trace("Skipping device because it is not a mouse (device handle): {}", deviceEntry.hDevice);
        }
    }

    return mice;
}

void WindowsMouseCaptor::populateWindowsMouse(WindowsMouse &mouse) {
    // get the device name
    constexpr UINT maxDeviceNameLength = 255;
    UINT deviceNameLength = maxDeviceNameLength;
    char deviceNameRaw[maxDeviceNameLength];

    deviceNameLength = GetRawInputDeviceInfo(mouse.handle, RIDI_DEVICENAME, &deviceNameRaw[0], &deviceNameLength);
    if (deviceNameLength <= 0) {
        // TODO: error
    }
    mouse.deviceName = std::string(deviceNameRaw);

    // get the remaining device info
    RID_DEVICE_INFO deviceInfo;
    deviceInfo.cbSize = sizeof(RID_DEVICE_INFO);
    UINT byteCount = sizeof(RID_DEVICE_INFO);
    byteCount = GetRawInputDeviceInfo(mouse.handle, RIDI_DEVICEINFO, &deviceInfo, &byteCount);

    if (byteCount <= 0) {
        // TODO: error
    }

    if (deviceInfo.dwType != RIM_TYPEMOUSE) {
        // TODO: error
    }

    auto mouseInfo = deviceInfo.mouse;
    mouse.id = mouseInfo.dwId;
    mouse.numberOfButtons = mouseInfo.dwNumberOfButtons;
    mouse.sampleRate = mouseInfo.dwSampleRate;
    mouse.hasHorizontalScrollWheel = mouseInfo.fHasHorizontalWheel;
}

void WindowsMouseCaptor::populateWindowsMice(std::vector<WindowsMouse> mice) {
    for (WindowsMouse &mouse : mice) {
        populateWindowsMouse(mouse);
    }
}

HWND WindowsMouseCaptor::createCaptorWindow() {
    static char szClassName[] = "Cells Interlinked Mouse Captor Window Class";
    auto selfHandle = GetModuleHandle(nullptr);

    WNDCLASS wc = {};
    wc.lpfnWndProc = &DefWindowProc;
    wc.hInstance = selfHandle;
    wc.lpszClassName = szClassName;
    auto registeredClass = RegisterClass(&wc);

    if (!registeredClass) {
        // TODO: error
    }

    auto hWindow = CreateWindowEx(0, szClassName, "Cells Interlinked Mouse Captor Window",
                                  WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
                                  CW_USEDEFAULT, CW_USEDEFAULT, nullptr, nullptr,
                                  selfHandle, nullptr);
    logger.debug("Created Mouse Captor window");

    if (hWindow == nullptr) {
        // TODO: error
    }

    return hWindow;
}

void WindowsMouseCaptor::registerMiceInputDevices(std::vector<WindowsMouse> mice, HWND hWindow) {
    auto rawInputDevices = std::unique_ptr<RAWINPUTDEVICE[]>(new RAWINPUTDEVICE[mice.size()]);

    for (int i = 0; i < mice.size(); i++) {
        auto mouse = mice[i];

        rawInputDevices[i].usUsagePage = HID_USAGE_PAGE_GENERIC;
        rawInputDevices[i].usUsage = HID_USAGE_GENERIC_MOUSE;
        rawInputDevices[i].dwFlags = RIDEV_INPUTSINK;
        rawInputDevices[i].hwndTarget = hWindow;
    }

    if (!RegisterRawInputDevices(rawInputDevices.get(), mice.size(), sizeof(RAWINPUTDEVICE))) {
        // TODO: error
    }
}

bool WindowsMouseCaptor::shouldHandleMessage(const MSG &msg) {
    if (msg.message != WM_INPUT) {
        // not a raw input message
        return false;
    }
}

bool WindowsMouseCaptor::shouldHandleRawInput(const RAWINPUT &rawInput) {
    if (rawInput.header.dwType != RIM_TYPEMOUSE) {
        // not a mouse, nothing to handle
        return false;
    }
    bool relative = (rawInput.data.mouse.usFlags & MOUSE_MOVE_RELATIVE) == MOUSE_MOVE_RELATIVE;
    if (!relative) {
        // we can only support relative raw input events
        // mostly because I don't know what would cause the other types to be dispatched
        return false;
    }

    return true;
}

void WindowsMouseCaptor::handleMessage(const MSG &msg) {
    if (!shouldHandleMessage(msg)) {
        return;
    }

    auto hRawInput = reinterpret_cast<HRAWINPUT>(msg.lParam);
    RAWINPUT rawInput;
    UINT rawInputCb = sizeof(RAWINPUT);
    auto responseCode = GetRawInputData(hRawInput, RID_INPUT, &rawInput, &rawInputCb, sizeof(RAWINPUTHEADER));
    if (responseCode < 0) {
        // TODO: error
    }

    if (shouldHandleRawInput(rawInput)) {
        const auto &mouse = rawInput.data.mouse;
//        logger.info("{}, {}", mouse.lLastX, mouse.lLastY);
    }
}


#endif // _WIN32