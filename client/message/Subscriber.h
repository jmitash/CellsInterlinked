
#ifndef CELLSINTERLINKED_SUBSCRIBER_H
#define CELLSINTERLINKED_SUBSCRIBER_H

#include <memory>

/**
 * An interface for message subscribers. Subscribers can be registered to receive an Event.
 * @tparam E the event type that this subscriber subscribes to
 */
template<typename E>
class Subscriber {
public:
    /**
     * Tells if this subscriber supports the given event.
     * @param event a pointer to the event to test the support of
     * @return true if this subscriber supports handling the given event, false otherwise
     */
    virtual bool supports(std::shared_ptr<E> event) = 0;

    /**
     * Handles the given event.
     * @param event the event to handle
     */
    virtual void handle(std::shared_ptr<E> event) = 0;
};


#endif //CELLSINTERLINKED_SUBSCRIBER_H
