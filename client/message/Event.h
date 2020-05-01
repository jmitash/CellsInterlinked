
#ifndef CELLSINTERLINKED_EVENT_H
#define CELLSINTERLINKED_EVENT_H

#include <string>
#include <utility>
#include <map>
#include <chrono>
#include <vector>

/**
 * Represent some event that occurred with the application. See Broker.
 */
class Event {

public:
    /**
     * Creates an event with the given information.
     * @param eventName the name of this event (typically similar to the subclass name)
     * @param priority the priority of this event (default 0)
     */
    explicit Event(std::string eventName, int priority = 0) : mEventName(std::move(eventName)), mPriority(priority) {}

    /**
     * Gets the name of this event. This is mainly to make debugging a little easier.
     * @return the name of this event
     */
    [[nodiscard]] std::string getEventName() const;

    /**
     * Gets the priority of this event. Lower numbers mean higher priority (processed first). Events with higher priority will get processed first. Note that starvation is possible.
     * @return the priority of this event
     */
    [[nodiscard]] int getPriority() const;

    /**
     * Gets the time that this event was created. This is used for debugging purposes and potentially to have messages expire if they go unprocessed after too long.
     * @return the time this event was created
     */
    [[nodiscard]] std::chrono::system_clock::time_point getCreationTime() const;

    [[nodiscard]] virtual std::string toString();

protected:
    std::map<std::string, std::string> getFieldMap() const;

    std::vector<std::string> getFieldMapStrings() const;

private:
    const std::string mEventName;
    const int mPriority;
    const std::chrono::system_clock::time_point mCreationTime = std::chrono::system_clock::now();
};


#endif //CELLSINTERLINKED_EVENT_H
