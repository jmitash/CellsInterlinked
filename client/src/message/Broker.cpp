
#include <fmt/format.h>
#include "message/Broker.h"

std::shared_ptr<PollableQueue> Broker::enroll(const std::shared_ptr<Subscriber> &subscriber) {
    auto subscriberQueue = std::make_shared<SubscriberQueue>(subscriber);
    mSubscriberQueues.push_back(subscriberQueue);
    return subscriberQueue;
}

void Broker::publish(const std::shared_ptr<Event> &event) {
    auto supportsEvent = [&](const std::shared_ptr<SubscriberQueue> &subscriberQueue) {
        return subscriberQueue->supportsEvent(event);
    };

    auto subscriberQueue = std::find_if(mSubscriberQueues.begin(), mSubscriberQueues.end(), supportsEvent);

    if (subscriberQueue == mSubscriberQueues.end()) {
        throw std::runtime_error(fmt::format("Could not find a supporting subscriber queue for event "
                                             "'{}'. Ensure that the required subscriber is enrolled before publishing.",
                                             event->getEventName()));
    }

    (*subscriberQueue)->addEvent(event);
}
