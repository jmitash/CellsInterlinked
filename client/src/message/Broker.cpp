
#include "../../include/message/Broker.h"

Broker *Broker::get() {
    static Broker broker;
    return &broker;
}

std::shared_ptr<PollableQueue<Event>> Broker::enroll(const std::shared_ptr<Subscriber<Event>> &subscriber) {
    auto subscriberQueue = std::make_shared<SubscriberQueue<Event>>(subscriber);
    mSubscriberQueues.push_back(subscriberQueue);
    return subscriberQueue;
}

void Broker::publish(const std::shared_ptr<Event> &event) {
    auto supportsEvent = [&](const std::shared_ptr<SubscriberQueue<Event>> &subscriberQueue) {
        return subscriberQueue->supportsEvent(event);
    };

    auto subscriberQueue = std::find_if(mSubscriberQueues.begin(), mSubscriberQueues.end(), supportsEvent);

    if (subscriberQueue->get() == nullptr) {
        throw std::runtime_error("Could not find a supporting subscriber queue for event. Ensure that the required "
                                 "subscriber is enrolled before publishing.");
    }

    subscriberQueue->get()->addEvent(event);
}
