
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
     * Gets the name for this monitor. This is usually the OS determined name for the device, and is not expected to have any human meaning, e.g. @code \\.\DISPLAY1\Monitor0 @endcode
     * @return the name of this monitor
     */
    [[nodiscard]] std::string getName() const;

    /**
     * Sets the name for this monitor. See getName().
     * @param name the name to set for this monitor
     */
    void setName(const std::string &name);

    /**
     * Gets the context name for this monitor. This is usually the driver name for the monitor.
     * @return the context name of this monitor
     */
    [[nodiscard]] std::string getContextName() const;

    /**
     * Sets the context name for this monitor. See getContextName().
     * @param contextName the context name to set for this monitor
     */
    void setContextName(const std::string &contextName);

    /**
     * Gets the number for this monitor, or -1 if not available. Monitors can be numbered by the operating system. This will be that number if assigned.
     * @return the number for this monitor
     */
    [[nodiscard]] int getNumber() const;

    /**
     * Sets the number for this monitor. See getMonitor();
     * @param number the number for this monitor
     */
    void setNumber(int number);

    /**
     * Tells if the monitor is on. Defaults to true if this is not supported by the machine/OS.
     * @return false if the monitor is detected as off, false otherwise
     */
    [[nodiscard]] bool isOn() const;

    /**
     * Sets whether this monitor is treated as on or not. See isOn().
     * @param on whether to set the monitor as on or not
     */
    void setOn(bool on);

    /**
     * Tells whether this monitor is treated as real or not. Some display devices may be considered virtual (not represented by a physical monitor). Defaults to true if this feature is not supported by the machine/OS.
     * @return false if this monitor is virtual, true otherwise
     */
    [[nodiscard]] bool isReal() const;

    /**
     * Sets whether this monitor is real or not. See isReal().
     * @param real whether to treat this monitor as real or not
     */
    void setReal(bool real);

    /**
     * Tells if this is the primary monitor for the machine. Most machines/OSs support the concept of a single primary monitor for the user with all other monitors as secondaries.
     * @return true if this is the primary monitor, false otherwise
     */
    [[nodiscard]] bool isPrimary() const;

    /**
     * Sets whether this monitor is primary or not. See isPrimary().
     * @param primary true if this is the primary monitor, false otherwise
     */
    void setPrimary(bool primary);

    /**
     * Tells the width in pixels of this monitor.
     * @return width in pixels of this monitor
     */
    [[nodiscard]] int getPixelWidth() const;

    /**
     * Sets the width in pixels of this monitor.
     * @param pixelWidth the width in pixels to set for this monitor
     */
    void setPixelWidth(int pixelWidth);

    /**
     * Gets the height in pixels of this monitor.
     * @return the height in pixels of this monitor
     */
    [[nodiscard]] int getPixelHeight() const;

    /**
     * Sets the height in pixels of this monitor.
     * @param pixelHeight the height in pixels of this monitor
     */
    void setPixelHeight(int pixelHeight);

    /**
     * Gets the left position of the monitor. This is used when there are multiple monitors for a single machine and describes the arrangement of monitors for that machine. This will be relative to the top left of the primary monitor.
     * @return the position of the left side of the screen in pixels
     */
    [[nodiscard]] int getPixelLeft() const;

    /**
     * Set the left position of the monitor. See getPixelLeft().
     * @param pixelLeft the position of the left side of the screen in pixels
     */
    void setPixelLeft(int pixelLeft);

    /**
     * Gets the top position of the monitor. This is used when there are multiple monitors for a single machine and describes the arrangement of monitors for that machine. This will be relative to the top left of the primary monitor.
     * @return the position of the top side of the screen in pixels
     */
    [[nodiscard]] int getPixelTop() const;

    /**
     * Set the top position of the monitor. See getPixelTop().
     * @param pixelTop the position of the top side of the screen in pixels
     */
    void setPixelTop(int pixelTop);

    /**
     * Gets the right position of the monitor. This is calculated from getPixelLeft() and getPixelWidth().
     * @return the position of the right side of the screen in pixels
     */
    [[nodiscard]] int getPixelRight() const;

    /**
     * Gets the bottom position of the monitor. This is calculated from getPixelTop() and getPixelHeight().
     * @return the position of the bottom side of the screen in pixels
     */
    [[nodiscard]] int getPixelBottom() const;

    /**
     * Gets the width in millimeters of this monitor. May not be supported for some monitors.
     * @return the width in millimeters of this monitor, or a non-positive value if not available
     */
    [[nodiscard]] float getMillimeterWidth() const;

    /**
     * Sets the width in millimeters of this monitor.
     * @param millimeterWidth the width in millimeters for this monitor
     */
    void setMillimeterWidth(float millimeterWidth);

    /**
     * Gets the height in millimeters of this monitor. May not be supported for some monitors.
     * @return the height in millimeters of this monitor, or a non-positive value if not available
     */
    [[nodiscard]] float getMillimeterHeight() const;

    /**
     * Sets the height in millimeters of this monitor.
     * @param millimeterHeight the height in millimeters for this monitor
     */
    void setMillimeterHeight(float millimeterHeight);

    /**
     * Writes the monitor as a string.
     * @return the string form of the monitor.
     */
    [[nodiscard]] std::string toString() const;

    /**
     * Tells if the monitor is "less than" the other. Determined by comparing individual fields' less thans.
     * @param rhs the monitor to compare against
     * @return true of the monitor is less than the other
     */
    bool operator<(const Monitor &rhs) const;

private:
    std::string mName;
    std::string mContextName;
    int mNumber = -1;
    bool mOn = true;
    bool mReal = true;
    bool mPrimary = true;
    int mPixelLeft = 0;
    int mPixelTop = 0;
    int mPixelWidth = -1;
    int mPixelHeight = -1;
    float mMillimeterWidth = -1;
    float mMillimeterHeight = -1;
};


#endif //CELLSINTERLINKED_MONITOR_H
