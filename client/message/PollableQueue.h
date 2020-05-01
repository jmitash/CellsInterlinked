
#ifndef CELLSINTERLINKED_POLLABLEQUEUE_H
#define CELLSINTERLINKED_POLLABLEQUEUE_H

/**
 * An event queue from which some events can be pulled from.
 * @tparam E the type of event this queue contains
 */
template<typename E>
class PollableQueue {
public:
    /**
     * Removes the highest priority event from the queue and returns it.
     * @param block whether to block until an event is available
     * @return the higher priority event from the queue
     */
    [[nodiscard]] virtual std::shared_ptr<E> popEvent(bool block) = 0;
};

#endif //CELLSINTERLINKED_POLLABLEQUEUE_H
