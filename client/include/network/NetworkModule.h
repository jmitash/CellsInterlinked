
#ifndef CELLSINTERLINKED_NETWORKMODULE_H
#define CELLSINTERLINKED_NETWORKMODULE_H

#include "application/Module.h"
#include "message/Broker.h"

/**
 * This module is responsible for connecting, receiving, and sending data to the server.
 */
class NetworkModule : public Module {
public:
    /**
     * Creates a network module with the given event broker.
     * @param broker the event broker to send and receive messages from
     */
    explicit NetworkModule(Broker *broker) : Module("NetworkModule"), mBroker(broker) {};
protected:
    bool executeIteration() override;

private:
    Broker *mBroker;
};


#endif //CELLSINTERLINKED_NETWORKMODULE_H
