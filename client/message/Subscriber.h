
#ifndef CELLSINTERLINKED_SUBSCRIBER_H
#define CELLSINTERLINKED_SUBSCRIBER_H

#include <memory>
#include <string>

/**
 * An interface for message subscribers. Subscribers can be enrolled with the Broker to receive an event queue.
 * @tparam E the event type that this subscriber will handle
 */
template<typename E>
class Subscriber {
public:
    /**
     * Creates a subscriber with the given name.
     */
    Subscriber(const std::string &name) : mName(name) {};

    /**
     * Gets the name of this subscriber. This should be unique.
     * @return the name of this subscriber
     */
    [[nodiscard]] virtual std::string getName() {
        return mName;
    }

    /**
     * Tells if this subscriber supports the given event.
     * @param event a pointer to the event to test the support of
     * @return true if this subscriber supports handling the given event, false otherwise
     */
    [[nodiscard]] virtual bool supports(std::shared_ptr<E> event) = 0;

private:
    const std::string mName;
};


#endif //CELLSINTERLINKED_SUBSCRIBER_H
