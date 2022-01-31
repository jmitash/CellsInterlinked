
#ifndef CELLSINTERLINKED_WINDOWSMOUSE_H
#define CELLSINTERLINKED_WINDOWSMOUSE_H

#ifdef _WIN32

#include <windows.h>
#include <spdlog/fmt/fmt.h>
#include "util/StringUtil.h"

/**
 * A mouse on Windows.
 */
class WindowsMouse {
public:
    /**
     * Gets the handles this mouse represents.
     *
     * @return the handle
     */
    [[nodiscard]] HANDLE getHandle() const;

    /**
     * Gets the device name this mouse represents.
     *
     * @return the device name
     */
    [[nodiscard]] std::string getDeviceName() const;

    /**
     * Gets the ID (known by Windows) that this mouse represents.
     *
     * @return the device ID
     */
    [[nodiscard]] DWORD getId() const;

    /**
     * Gets the number of buttons the mouse has.
     *
     * @return the number of buttons
     */
    [[nodiscard]] DWORD getNumberOfButtons() const;

    /**
     * Gets the sample rate for the mouse.
     *
     * @return the sample rate
     */
    [[nodiscard]] DWORD getSampleRate() const;

    /**
     * Tells whether the mouse has a horizontal scroll wheel.
     *
     * @return true if the mouse has a horizontal scroll wheel, false otherwise
     */
    [[nodiscard]] BOOL getHasHorizontalScrollWheel() const;

    /**
     * Sets the handle. See getHandle().
     *
     * @param handle the handle to set
     */
    void setHandle(HANDLE handle);

    /**
     * Sets the device name. See getDeviceName().
     *
     * @param deviceName the device name
     */
    void setDeviceName(const std::string &deviceName);

    /**
     * Sets the device ID. See getId().
     *
     * @param id the ID of the device
     */
    void setId(DWORD id);

    /**
     * Sets the number of buttons on this mouse. See getNumberOfButtons().
     *
     * @param numberOfButtons the number of buttons
     */
    void setNumberOfButtons(DWORD numberOfButtons);

    /**
     * Sets the sample rate. See getSampleRate().
     *
     * @param sampleRate the sample rate
     */
    void setSampleRate(DWORD sampleRate);

    /**
     * Sets whether the mouse has a horizontal scroll wheel or not. See getHasHorizontalScrollWheel().
     *
     * @param hasHorizontalScrollWheel has horizontal scroll wheel
     */
    void setHasHorizontalScrollWheel(BOOL hasHorizontalScrollWheel);

    /**
     * Gets a string version of the mouse.
     *
     * @return the mouse as a string
     */
    [[nodiscard]] std::string toString() const;

    /**
     * Tells if the Windows Mouse is "less than" the other. Determined by comparing individual fields' less thans.
     * @param rhs the Windows Mouse to compare against
     * @return true if the Windows Mouse is less than the other
     */
    bool operator<(const WindowsMouse &rhs) const;

    /**
     * Tells if the Windows Mouse is the same as another. Determined by comparing individual fields' values.
     * @param rhs the Windows Mouse to compare against
     * @return true if the Windows Mouse is the same the other
     */
    bool operator==(const WindowsMouse &rhs) const;

private:
    HANDLE mHandle;
    std::string mDeviceName;
    DWORD mId;
    DWORD mNumberOfButtons;
    DWORD mSampleRate;
    BOOL mHasHorizontalScrollWheel;
};

#else // not _WIN32

/**
 * A mouse on Windows.
 */
class WindowsMouse {

};

#endif

#endif //CELLSINTERLINKED_WINDOWSMOUSE_H
