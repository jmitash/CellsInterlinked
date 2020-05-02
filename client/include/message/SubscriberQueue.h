
#ifndef CELLSINTERLINKED_SUBSCRIBERQUEUE_H
#define CELLSINTERLINKED_SUBSCRIBERQUEUE_H

#include <queue>
#include <memory>
#include <functional>
#include <mutex>
#include <thread>
#include <stdexcept>

#include "Subscriber.h"
#include "Event.h"
#include "PollableQueue.h"


/**
 * A combination of a subscriber and its queue of events. Used to maintain the queue for each subscriber and handle the additions and removals to and from the queue. Note that events have priority which can determine their place within the queue. SubscriberQueue is thread safe and uses a mutex to make modification to the queue.
 * @tparam E the event type this manages
 */
template<typename E>
class SubscriberQueue : public PollableQueue<E> {
public:
    /**
     * Creates a new subscriber queue with the given subscriber.
     * @param subscriber the subscriber this will maintain
     */
    SubscriberQueue(const std::shared_ptr<Subscriber<E>> &subscriber) : mSubscriber(subscriber) {}

    /**
     * Copy constructor that throws an exception. Intended to allow this to work in vectors.
     * @param rhs the right hand side of the copy operation (the object to copy from)
     */
    SubscriberQueue(const SubscriberQueue<E> &rhs) {
        throw std::runtime_error("This SubscriberQueue copy constructor should never be called.");
    }

    /**
     * Move constructor for a subscriber queue. Includes special handling for the mutex.
     * @param rhs the right hand side of the move operation (where to copy from)
     */
    SubscriberQueue(SubscriberQueue<E> &&rhs) noexcept {
        std::lock_guard<std::mutex> queueGuard(rhs.mQueueMutex);

        this->mQueue = std::move(rhs.mQueue);
        this->mSubscriber = std::move(mSubscriber);
    }

    /**
     * Tells if this subscriber queue supports the given event.
     * @param event the event to test support of
     * @return true if this supports the event and it can be added to the queue, false otherwise
     */
    bool supportsEvent(const std::shared_ptr<E> &event) const {
        return mSubscriber->supports(event);
    }

    /**
     * Adds the given event to the queue. The event should be testing using #supportsEvent(std::shared_ptr<Event>) beforehand.
     * @param event the event to add to the queue
     */
    void addEvent(const std::shared_ptr<E> &event) {
        std::lock_guard<std::mutex> queueGuard(mQueueMutex);

        mQueue.push(event);
    }

    std::shared_ptr<E> popEvent(bool block) override {
        std::unique_lock<std::mutex> queueGuard(mQueueMutex);

        if (mQueue.empty() && !block) {
            return std::shared_ptr<E>(nullptr);
        } else if (mQueue.empty() && block) {
            while (mQueue.empty()) {
                // release lock while we yield
                queueGuard.unlock();
                std::this_thread::yield();

                // done yielding, acquire lock while test the queue size and potentially get an event
                queueGuard.lock();
            }
        }

        std::shared_ptr<E> event = mQueue.top();
        mQueue.pop();
        return event;
    }

private:
    struct PriorityPointerComparator {
        bool operator()(std::shared_ptr<E> leftHand, std::shared_ptr<E> rightHand) {
            return leftHand->getPriority() < rightHand->getPriority();
        }
    };

    std::shared_ptr<Subscriber<E>> mSubscriber;
    std::priority_queue<std::shared_ptr<E>, std::vector<std::shared_ptr<E>>, PriorityPointerComparator> mQueue;
    std::mutex mQueueMutex;
};


#endif //CELLSINTERLINKED_SUBSCRIBERQUEUE_H
