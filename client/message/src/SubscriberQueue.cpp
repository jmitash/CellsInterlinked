
#include "../SubscriberQueue.h"

#include <thread>
#include <stdexcept>

SubscriberQueue::SubscriberQueue(const SubscriberQueue &rhs) {
    throw std::runtime_error("This SubscriberQueue copy constructor should never be called.");
}

SubscriberQueue::SubscriberQueue(SubscriberQueue &&rhs) noexcept {
    std::lock_guard<std::mutex> queueGuard(rhs.mQueueMutex);

    this->mQueue = std::move(rhs.mQueue);
    this->mSubscriber = std::move(mSubscriber);
}

bool SubscriberQueue::supportsEvent(const std::shared_ptr<Event> &event) const {
    return mSubscriber->supports(event);
}

void SubscriberQueue::addEvent(const std::shared_ptr<Event> &event) {
    std::lock_guard<std::mutex> queueGuard(mQueueMutex);

    mQueue.push(event);
}

std::shared_ptr<Event> SubscriberQueue::popEvent(bool block) {
    std::unique_lock<std::mutex> queueGuard(mQueueMutex);

    if (mQueue.empty() && !block) {
        return std::shared_ptr<Event>(nullptr);
    } else if (mQueue.empty() && block) {
        while (mQueue.empty()) {
            // release lock while we yield
            queueGuard.unlock();
            std::this_thread::yield();

            // done yielding, acquire lock while test the queue size and potentially get an event
            queueGuard.lock();
        }
    }

    std::shared_ptr<Event> event = mQueue.top();
    mQueue.pop();
    return event;
}


