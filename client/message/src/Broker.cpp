
#include "../Broker.h"

Broker &Broker::get() {
    static Broker broker;
    return broker;
}

void Broker::subscribe(const std::shared_ptr<Subscriber<Event>> &subscriber) {
    mSubscriberQueues.emplace_back(subscriber);
}

void Broker::publish(const std::shared_ptr<Event> &event) {
    auto supportsEvent = [&](const SubscriberQueue &subscriberQueue) {
        return subscriberQueue.supportsEvent(event);
    };

    auto subscriberQueue = std::find_if(mSubscriberQueues.begin(), mSubscriberQueues.end(), supportsEvent);
    subscriberQueue->addEvent(event);
}
