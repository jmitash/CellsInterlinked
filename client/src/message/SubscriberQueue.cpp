
#include <message/SubscriberQueue.h>

std::shared_ptr<Event> SubscriberQueue::popEvent(bool block, std::chrono::milliseconds timeout) {
    auto startTime = std::chrono::system_clock::now();

    std::unique_lock<std::mutex> queueGuard(mQueueMutex);

    if (mQueue.empty() && !block) {
        return std::shared_ptr<Event>(nullptr);
    } else if (mQueue.empty() && block) {
        while (mQueue.empty()) {
            // release lock while we yield
            queueGuard.unlock();
            if (startTime + timeout < std::chrono::system_clock::now()) {
                // timed out
                return std::shared_ptr<Event>(nullptr);
            }
            std::this_thread::yield();

            // done yielding, acquire lock while test the queue size and potentially get an event
            queueGuard.lock();
        }
    }

    std::shared_ptr<Event> event = mQueue.top();
    mQueue.pop();
    return event;
}
