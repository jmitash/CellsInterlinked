
#ifndef CELLSINTERLINKED_BROKER_H
#define CELLSINTERLINKED_BROKER_H

#include <vector>

#include "SubscriberQueue.h"

class Broker {
public:

    /**
     * Gets the singleton Broker instance.
     * @return the singleton broker instance
     */
    static Broker &get();

    // TODO: Is this really a "subscribe"?
    void subscribe(const std::shared_ptr<Subscriber<Event>> &subscriber);

    void publish(const std::shared_ptr<Event> &event);

private:
    Broker() = default;

    std::vector<SubscriberQueue> mSubscriberQueues;

};


#endif //CELLSINTERLINKED_BROKER_H
