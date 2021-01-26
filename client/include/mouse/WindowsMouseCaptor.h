

#ifndef CELLSINTERLINKED_WINDOWSMOUSECAPTOR_H
#define CELLSINTERLINKED_WINDOWSMOUSECAPTOR_H

#include "mouse/MouseCaptor.h"

#ifdef _WIN32

#include <windows.h>
#include "logging/LogHelper.h"

/**
 * Captor for mice on Windows machines.
 */
class WindowsMouseCaptor : public MouseCaptor {

public:
    void run() override;

    struct WindowsMouse {
        HANDLE handle;
        std::string deviceName;
        DWORD id;
        DWORD numberOfButtons;
        DWORD sampleRate;
        BOOL hasHorizontalScrollWheel;
    };
private:
    /**
     * Gathers mice on the system. The WindowsMouse that are created have only the HANDLE populated.
     * @return the mice on the system
     */
    std::vector<WindowsMouse> getWindowsMice();

    /**
     * Populates detailed information on the mouse. Uses the handle from the mouse to pull more information.
     * @param mouse the mouse to populate
     */
    void populateWindowsMouse(WindowsMouse &mouse);

    /**
     * Populates detailed information on the mice.
     * @param mice the mice to populate
     */
    void populateWindowsMice(std::vector<WindowsMouse> mice);

    /**
     * Creates a window (not shown) which is utilized to capture input messages from Windows. The window is required to receive the message events.
     * @return a handle to the created window
     */
    HWND createCaptorWindow();

    /**
     * Registers mice as raw input devices. This allows capturing of raw input messages from the mice.
     * @param mice the mice to register
     * @param hWindow the handle to the window used to capture events
     */
    void registerMiceInputDevices(std::vector<WindowsMouse> mice, HWND hWindow);

    /**
     * Handle a received message from the Windows message loop.
     * @param msg the message to handle
     */
    void handleMessage(const MSG &msg);

    /**
     * Tells whether a given message is relevant to this captor and if it should be handled.
     * @param msg the message to determine relevancy of
     * @return true if the message should be handled, false otherwise
     */
    bool shouldHandleMessage(const MSG &msg);

    /**
     * Tells whether the raw input should be handled by this captor.
     * @param rawInput the raw input to test
     * @return true if the raw input should be handled, false otherwise
     */
    bool shouldHandleRawInput(const RAWINPUT &rawInput);

    inline static auto logger = LogHelper::logger(__FILE__);
};

#else // not _WIN32

class WindowsMouseCaptor : public MouseCaptor {

};

#endif

#endif //CELLSINTERLINKED_WINDOWSMOUSECAPTOR_H
