
#ifndef CELLSINTERLINKED_NETWORKMODULE_H
#define CELLSINTERLINKED_NETWORKMODULE_H

#include "application/Module.h"
#include "message/Broker.h"
#include "network/SerializableClientEventSubscriber.h"

/**
 * This module is responsible for connecting, receiving, and sending data to the server.
 */
class NetworkModule : public Module {
public:
    /**
     * Creates a network module with the given event broker.
     * @param broker the event broker to send and receive messages from
     */
    explicit NetworkModule(Broker *broker)
            : Module("NetworkModule"),
              mBroker(broker),
              mSerializableClientEventQueue(broker->enroll(std::make_shared<SerializableClientEventSubscriber>())) {};

protected:
    bool executeIteration() override;

private:
    Broker *mBroker;
    std::shared_ptr<PollableQueue> mSerializableClientEventQueue;
};


#endif //CELLSINTERLINKED_NETWORKMODULE_H
