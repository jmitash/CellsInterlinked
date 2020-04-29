
#ifndef CELLSINTERLINKED_TESTEVENT_H
#define CELLSINTERLINKED_TESTEVENT_H

#include "Event.h"

class TestEvent : public Event {
public:
    TestEvent(const std::string &sourceName, const std::string &eventName);
};


#endif //CELLSINTERLINKED_TESTEVENT_H
