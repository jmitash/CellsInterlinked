
#include <date/date.h>

#include "../Event.h"

std::string Event::getSourceName() const {
    return mSourceName;
}

std::string Event::getEventName() const {
    return std::string();
}

std::chrono::system_clock::time_point Event::getCreationTime() const {
    return mCreationTime;
}

std::string Event::toString() {
    const auto fieldMapStrings = getFieldMapStrings();
    std::stringstream result; // TODO: Remove extraneous delimiter
    std::copy(fieldMapStrings.begin(), fieldMapStrings.end(), std::ostream_iterator<std::string>(result, ", "));
    return result.str();
}

std::map<std::string, std::string> Event::getFieldMap() const {
    std::map<std::string, std::string> fields; // TODO: order-preserving map implementation
    const std::string formattedCreationTime = date::format("%FT%TZ", getCreationTime());

    fields.insert(std::make_pair("sourceName", getSourceName()));
    fields.insert(std::make_pair("eventName", getEventName()));
    fields.insert(std::make_pair("creationTime", formattedCreationTime));

    return fields;
}

std::vector<std::string> Event::getFieldMapStrings() const {
    auto fieldMap = getFieldMap();
    std::vector<std::string> output;

    for (const auto &pair : getFieldMap()) {
        output.push_back(pair.first + "=" + pair.second);
    }

    return output;
}