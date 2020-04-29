
#include "../TestSubscriber.h"

bool TestSubscriber::supports(std::shared_ptr<TestEvent> event) {
    return true;
}

void TestSubscriber::handle(std::shared_ptr<TestEvent> event) {
    logger.info(event->toString());
}
