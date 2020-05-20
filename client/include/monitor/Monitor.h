
#ifndef CELLSINTERLINKED_MONITOR_H
#define CELLSINTERLINKED_MONITOR_H

#include <string>
#include <queue>
#include <vector>

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
    [[nodiscard]] virtual std::string toString() const;

    /**
     * Tells if the monitor is "less than" the other. Determined by comparing individual fields' less thans.
     * @param rhs the monitor to compare against
     * @return true if the monitor is less than the other
     */
    bool operator<(const Monitor &rhs) const;

    /**
     * Tells if the monitor is the same as another. Determined by comparing individual fields' values.
     * @param rhs the monitor to compare against
     * @return true if the monitor is the same the other
     */
    bool operator==(const Monitor &rhs) const;

    /**
     * Serialize this monitor into a vector of bytes.
     * @return a vector of bytes representing this monitor
     */
    [[nodiscard]] virtual std::vector<unsigned char> serialize() const;

    /**
     * Deserialize a monitor from a buffer.
     * @param monitor the monitor to deserialize into
     * @param buffer the buffer to deserialize data from
     * @return a monitor based on the data from the buffer
     */
    static void deserialize(Monitor &monitor, std::queue<unsigned char> &buffer);

private:
    std::string mName;
    std::string mContextName;
    int mNumber = -1;
    bool mPrimary = true;
    int mPixelLeft = 0;
    int mPixelTop = 0;
    int mPixelWidth = -1;
    int mPixelHeight = -1;
    float mMillimeterWidth = -1;
    float mMillimeterHeight = -1;
};


#endif //CELLSINTERLINKED_MONITOR_H
