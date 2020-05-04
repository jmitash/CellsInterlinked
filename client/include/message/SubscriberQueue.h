
#ifndef CELLSINTERLINKED_SUBSCRIBERQUEUE_H
#define CELLSINTERLINKED_SUBSCRIBERQUEUE_H

#include <queue>
#include <memory>
#include <functional>
#include <mutex>
#include <thread>
#include <stdexcept>
#include <utility>

#include "Subscriber.h"
#include "Event.h"
#include "PollableQueue.h"

/**
 * A combination of a subscriber and its queue of events. Used to maintain the queue for each subscriber and handle the additions and removals to and from the queue. Note that events have priority which can determine their place within the queue. SubscriberQueue is thread safe and uses a mutex to make modification to the queue.
 */
class SubscriberQueue : public PollableQueue {
public:
    /**
     * Creates a new subscriber queue with the given subscriber.
     * @param subscriber the subscriber this will maintain
     */
    explicit SubscriberQueue(std::shared_ptr<Subscriber> subscriber) : mSubscriber(std::move(subscriber)) {}

    /**
     * Copy constructor that throws an exception. Intended to allow this to work in vectors.
     * @param rhs the right hand side of the copy operation (the object to copy from)
     */
    SubscriberQueue(const SubscriberQueue &rhs) {
        throw std::runtime_error("This SubscriberQueue copy constructor should never be called.");
    }

    /**
     * Move constructor for a subscriber queue. Includes special handling for the mutex.
     * @param rhs the right hand side of the move operation (where to copy from)
     */
    SubscriberQueue(SubscriberQueue &&rhs) noexcept {
        std::lock_guard<std::mutex> queueGuard(rhs.mQueueMutex);

        this->mQueue = std::move(rhs.mQueue);
        this->mSubscriber = std::move(mSubscriber);
    }

    /**
     * Tells if this subscriber queue supports the given event.
     * @param event the event to test support of
     * @return true if this supports the event and it can be added to the queue, false otherwise
     */
    [[nodiscard]] bool supportsEvent(const std::shared_ptr<Event> &event) const {
        return mSubscriber->supports(event);
    }

    /**
     * Adds the given event to the queue. The event should be testing using #supportsEvent(std::shared_ptr<Event>) beforehand.
     * @param event the event to add to the queue
     */
    void addEvent(const std::shared_ptr<Event> &event) {
        std::lock_guard<std::mutex> queueGuard(mQueueMutex);

        mQueue.push(event);
    }

    std::shared_ptr<Event> popEvent(bool block, std::chrono::milliseconds timeout) override;

private:
    struct PriorityPointerComparator {
        bool operator()(const std::shared_ptr<Event> &leftHand, const std::shared_ptr<Event> &rightHand) {
            return leftHand->getPriority() < rightHand->getPriority();
        }
    };

    std::shared_ptr<Subscriber> mSubscriber;
    std::priority_queue<std::shared_ptr<Event>, std::vector<std::shared_ptr<Event>>, PriorityPointerComparator> mQueue;
    std::mutex mQueueMutex;
};


#endif //CELLSINTERLINKED_SUBSCRIBERQUEUE_H
