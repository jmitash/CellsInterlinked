
#ifndef CELLSINTERLINKED_BROKER_H
#define CELLSINTERLINKED_BROKER_H

#include <vector>

#include "SubscriberQueue.h"

/**
 * A singleton message broker for the application. This is the main interface for publishing events and event queue management.
 */
class Broker {
public:
    /**
     * Gets the singleton Broker instance.
     * @return the singleton broker instance
     */
    [[nodiscard]] static Broker *get();

    /**
     * Registers a subscriber with the broker, producing a SubscriberQueue that will be able to receive events. The registerer is ultimately responsible from pulling events from the queue.
     * @param subscriber the subscriber to set up an event queue for
     */
    [[nodiscard]] std::shared_ptr<PollableQueue> enroll(const std::shared_ptr<Subscriber> &subscriber);

    /**
     * Publish an event. The correct queue for the event will be determined, and then the event will be added to that queue.
     * @param event the event to add to the queue
     * @throws std::runtime_error when no enrolled queue supports the given event
     */
    void publish(const std::shared_ptr<Event> &event);

private:
    Broker() = default;

    std::vector<std::shared_ptr<SubscriberQueue>> mSubscriberQueues;

};


#endif //CELLSINTERLINKED_BROKER_H
