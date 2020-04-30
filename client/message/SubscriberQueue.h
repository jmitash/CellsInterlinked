
#ifndef CELLSINTERLINKED_SUBSCRIBERQUEUE_H
#define CELLSINTERLINKED_SUBSCRIBERQUEUE_H

#include <queue>
#include <memory>
#include <functional>
#include <mutex>

#include "Subscriber.h"
#include "Event.h"


/**
 * A combination of a subscriber and its queue of events. Used to maintain the queue for each subscriber and handle the additions and removals to and from the queue. Note that events have priority which can determine their place within the queue. SubscriberQueue is thread safe and uses a mutex to make modification to the queue.
 */
class SubscriberQueue {
public:
    /**
     * Creates a new subscriber queue with the given subscriber.
     * @param subscriber the subscriber this will maintain
     */
    SubscriberQueue(const std::shared_ptr<Subscriber<Event>> &subscriber) : mSubscriber(subscriber) {}

    /**
     * Copy constructor that throws an exception. Intended to allow this to work in vectors.
     * @param rhs the right hand side of the copy operation (the object to copy from)
     */
    SubscriberQueue(const SubscriberQueue &rhs);

    /**
     * Move constructor for a subscriber queue. Includes special handling for the mutex.
     * @param rhs the right hand side of the move operation (where to copy from)
     */
    SubscriberQueue(SubscriberQueue &&rhs) noexcept;

    /**
     * Tells if this subscriber queue supports the given event.
     * @param event the event to test support of
     * @return true if this supports the event and it can be added to the queue, false otherwise
     */
    bool supportsEvent(const std::shared_ptr<Event> &event) const;

    /**
     * Adds the given event to the queue. The event should be testing using #supportsEvent(std::shared_ptr<Event>) beforehand.
     * @param event the event to add to the queue
     */
    void addEvent(const std::shared_ptr<Event> &event);

    /**
     * Removes the highest priority event from the queue and returns it.
     * @param block whether to block until an event is available
     * @return the higher priority event from the queue
     */
    std::shared_ptr<Event> popEvent(bool block);

private:
    struct EventPointerComparator {
        bool operator()(std::shared_ptr<Event> leftHand, std::shared_ptr<Event> rightHand) {
            return leftHand->getPriority() < rightHand->getPriority();
        }
    };

    std::shared_ptr<Subscriber<Event>> mSubscriber;
    std::priority_queue<std::shared_ptr<Event>, std::vector<std::shared_ptr<Event>>, EventPointerComparator> mQueue;
    std::mutex mQueueMutex;
};


#endif //CELLSINTERLINKED_SUBSCRIBERQUEUE_H
