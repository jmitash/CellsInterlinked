
#ifndef CELLSINTERLINKED_EVENT_H
#define CELLSINTERLINKED_EVENT_H

#include <string>
#include <utility>
#include <map>
#include <chrono>
#include <vector>

class Event {

public:
    /**
     * Creates an event with the given source name and event name.
     * @param sourceName the name of the source that created this event
     * @param eventName the name of this event
     * @param priority the priority of this event (default 0, lower numbers mean higher priority)
     */
    explicit Event(std::string sourceName, std::string eventName, int priority = 0)
            : mSourceName(std::move(sourceName)),
              mEventName(std::move(eventName)),
              mPriority(priority) {}

    [[nodiscard]] std::string getSourceName() const;

    [[nodiscard]] std::string getEventName() const;

    [[nodiscard]] int getPriority() const;

    [[nodiscard]] std::chrono::system_clock::time_point getCreationTime() const;

    [[nodiscard]] virtual std::string toString();

protected:
    std::map<std::string, std::string> getFieldMap() const;

    std::vector<std::string> getFieldMapStrings() const;

private:
    const std::string mSourceName;
    const std::string mEventName;
    const int mPriority;
    const std::chrono::system_clock::time_point mCreationTime = std::chrono::system_clock::now();
};


#endif //CELLSINTERLINKED_EVENT_H
