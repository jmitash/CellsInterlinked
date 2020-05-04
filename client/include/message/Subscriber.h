
#ifndef CELLSINTERLINKED_SUBSCRIBER_H
#define CELLSINTERLINKED_SUBSCRIBER_H

#include <memory>
#include <string>
#include <utility>
#include "Event.h"

/**
 * An interface for message subscribers. Subscribers can be enrolled with the Broker to receive an event queue.
 */
class Subscriber {
public:
    /**
     * Creates a subscriber with the given name.
     */
    explicit Subscriber(std::string name) : mName(std::move(name)) {};

    /**
     * Gets the name of this subscriber. This should be unique.
     * @return the name of this subscriber
     */
    [[nodiscard]] std::string getName() {
        return mName;
    }

    /**
     * Tells if this subscriber supports the given event.
     * @param event a pointer to the event to test the support of
     * @return true if this subscriber supports handling the given event, false otherwise
     */
    [[nodiscard]] bool supports(const std::shared_ptr<Event> &event) {
        return castEvent(event) != nullptr;
    }

protected:
    /**
     * Casts the given event to the one supported by this subscriber.
     * @param event the event to cast
     * @return the casted event, or an empty pointer if the cast was not possible
     */
    [[nodiscard]] virtual std::shared_ptr<Event> castEvent(const std::shared_ptr<Event> &event) = 0;

private:
    const std::string mName;
};


#endif //CELLSINTERLINKED_SUBSCRIBER_H
