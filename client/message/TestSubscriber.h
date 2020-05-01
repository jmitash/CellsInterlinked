
#ifndef CELLSINTERLINKED_TESTSUBSCRIBER_H
#define CELLSINTERLINKED_TESTSUBSCRIBER_H

#include "Subscriber.h"
#include "TestEvent.h"
#include "../../common/logging/LogHelper.h"

class TestSubscriber : public Subscriber<TestEvent> {
public:
    TestSubscriber() : Subscriber("TestSubscriber") {}

    std::string getName() override;

    bool supports(std::shared_ptr<TestEvent> event) override;

private:
    spdlog::logger logger = LogHelper::logger(__FILE__);
};


#endif //CELLSINTERLINKED_TESTSUBSCRIBER_H
