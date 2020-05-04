
#ifndef CELLSINTERLINKED_POLLABLEQUEUE_H
#define CELLSINTERLINKED_POLLABLEQUEUE_H

#include <chrono>

/**
 * An event queue from which some events can be pulled from.
 */
class PollableQueue {
public:
    /**
     * Removes the highest priority event from the queue and returns it. Does not block.
     * @return the higher priority event from the queue
     */
    [[nodiscard]] virtual std::shared_ptr<Event> popEvent() {
        return popEvent(false, std::chrono::milliseconds(0));
    }

    /**
     * Removes the highest priority event from the queue and returns it. Blocks and waits for an event if specified.
     * @param block whether to block until an event is available
     * @param timeout the milliseconds to wait before timing out if blocking
     * @return the higher priority event from the queue
     */
    [[nodiscard]] virtual std::shared_ptr<Event> popEvent(bool block, std::chrono::milliseconds timeout) = 0;
};

#endif //CELLSINTERLINKED_POLLABLEQUEUE_H
