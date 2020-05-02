
#include "../../include/message/TestSubscriber.h"


std::string TestSubscriber::getName() {
    return "TestSubscriber";
}

bool TestSubscriber::supports(std::shared_ptr<TestEvent> event) {
    return true;
}
