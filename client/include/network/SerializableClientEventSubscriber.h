
#ifndef CELLSINTERLINKED_SERIALIZABLECLIENTEVENTSUBSCRIBER_H
#define CELLSINTERLINKED_SERIALIZABLECLIENTEVENTSUBSCRIBER_H

#include "message/Subscriber.h"
#include "network/SerializableClientEvent.h"

/**
 * A subscriber to SerializableClientEvent events.
 */
class SerializableClientEventSubscriber : public Subscriber {
public:
    /**
     * Constructs a serializable event subscriber.
     */
    SerializableClientEventSubscriber() : Subscriber("SerializableClientEventSubscriber") {};

protected:
    std::shared_ptr<Event> castEvent(const std::shared_ptr<Event> &event) override {
        return std::dynamic_pointer_cast<SerializableClientEvent>(event);
    }
};


#endif //CELLSINTERLINKED_SERIALIZABLECLIENTEVENTSUBSCRIBER_H
