
#include "message/TestSubscriber.h"


std::shared_ptr<Event> TestSubscriber::castEvent(const std::shared_ptr<Event> &event) {
    return std::dynamic_pointer_cast<TestEvent>(event);
}
