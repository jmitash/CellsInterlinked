//
// Created by jacob on 4/19/2020.
//

#ifndef CELLSINTERLINKED_MONITOR_H
#define CELLSINTERLINKED_MONITOR_H

#include <string>

/**
 * Representation of a monitor or display device for a machine.
 */
class Monitor {
public:

    /**
     * Constructs a monitor with all default values. Values should be populated when available through setters.
     */
    Monitor() = default;

    /**
     * Gets the m_name for this monitor. This is usually the OS determined m_name for the device, and is not expected to have any human meaning, e.g. @code \\.\DISPLAY1\Monitor0 @endcode
     * @return the m_name of this monitor
     */
    std::string getName() const;

    /**
     * Sets the m_name for this monitor. See getName().
     * @param name the m_name to set for this monitor
     */
    void setName(const std::string &name);

    /**
     * Gets the context m_name for this monitor. This is usually the driver m_name for the monitor.
     * @return the context m_name of this monitor
     */
    std::string getContextName() const;

    /**
     * Sets the context m_name for this monitor. See getContextName().
     * @param contextName the context m_name to set for this monitor
     */
    void setContextName(const std::string &contextName);

    /**
     * Gets the number for this monitor, or -1 if not available. Monitors can be numbered by the operating system. This will be that number if assigned.
     * @return the number for this monitor
     */
    int getNumber() const;

    /**
     * Sets the number for this monitor. See getMonitor();
     * @param number the number for this monitor
     */
    void setNumber(int number);

    /**
     * Tells if the monitor is on. Defaults to true if this is not supported by the machine/OS.
     * @return false if the monitor is detected as off, false otherwise
     */
    bool isOn() const;

    /**
     * Sets whether this monitor is treated as on or not. See isOn().
     * @param on whether to set the monitor as on or not
     */
    void setOn(bool on);

    /**
     * Tells whether this monitor is treated as real or not. Some display devices may be considered virtual (not represented by a physical monitor). Defaults to true if this feature is not supported by the machine/OS.
     * @return false if this monitor is virtual, true otherwise
     */
    bool isReal() const;

    /**
     * Sets whether this monitor is real or not. See isReal().
     * @param real whether to treat this monitor as real or not
     */
    void setReal(bool real);

    /**
     * Tells if this is the primary monitor for the machine. Most machines/OSs support the concept of a single primary monitor for the user with all other monitors as secondaries.
     * @return true if this is the primary monitor, false otherwise
     */
    bool isPrimary() const;

    /**
     * Sets whether this monitor is primary or not. See isPrimary().
     * @param primary true if this is the primary monitor, false otherwise
     */
    void setPrimary(bool primary);

    /**
     * Tells the width in pixels of this monitor.
     * @return width in pixels of this monitor
     */
    int getPixelWidth() const;

    /**
     * Sets the width in pixels of this monitor.
     * @param pixelWidth the width in pixels to set for this monitor
     */
    void setPixelWidth(int pixelWidth);

    /**
     * Gets the height in pixels of this monitor.
     * @return the height in pixels of this monitor
     */
    int getPixelHeight() const;

    /**
     * Sets the height in pixels of this monitor.
     * @param pixelHeight the height in pixels of this monitor
     */
    void setPixelHeight(int pixelHeight);

    /**
     * Gets the width in millimeters of this monitor. May not be supported for some monitors.
     * @return the width in millimeters of this monitor, or a non-positive value if not available
     */
    float getMillimeterWidth() const;

    /**
     * Sets the width in millimeters of this monitor.
     * @param millimeterWidth the width in millimeters for this monitor
     */
    void setMillimeterWidth(float millimeterWidth);

    /**
     * Gets the height in millimeters of this monitor. May not be supported for some monitors.
     * @return the height in millimeters of this monitor, or a non-positive value if not available
     */
    float getMillimeterHeight() const;

    /**
     * Sets the height in millimeters of this monitor.
     * @param millimeterHeight the height in millimeters for this monitor
     */
    void setMillimeterHeight(float millimeterHeight);

private:
    std::string mName;
    std::string mContextName;
    int mNumber = -1;
    bool mOn = true;
    bool mReal = true;
    bool mPrimary = true;
    int mPixelWidth;
    int mPixelHeight;
    float mMillimeterWidth;
    float mMillimeterHeight;
};


#endif //CELLSINTERLINKED_MONITOR_H
