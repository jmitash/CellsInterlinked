
#ifndef CELLSINTERLINKED_TESTSUBSCRIBER_H
#define CELLSINTERLINKED_TESTSUBSCRIBER_H

#include "Subscriber.h"
#include "TestEvent.h"
#include "logging/LogHelper.h"

class TestSubscriber : public Subscriber {
public:
    TestSubscriber() : Subscriber("TestSubscriber") {}

protected:
    std::shared_ptr<Event> castEvent(const std::shared_ptr<Event> &event) override;

private:
    spdlog::logger logger = LogHelper::logger(__FILE__);
};


#endif //CELLSINTERLINKED_TESTSUBSCRIBER_H
