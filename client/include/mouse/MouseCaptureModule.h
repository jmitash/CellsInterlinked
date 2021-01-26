
#ifndef CELLSINTERLINKED_MOUSECAPTUREMODULE_H
#define CELLSINTERLINKED_MOUSECAPTUREMODULE_H

#include "application/Module.h"
#include "message/Broker.h"

/**
 * Module responsible for capturing (and potentially cancelling) actions of the mouse. This includes both mouse
 * movements and button presses.
 */
class MouseCaptureModule : public Module {
public:
    /**
     * Creates a mouse capture module that will use the given broker.
     * @param broker the broker to use for publishing/subscribing to mouse events
     */
    explicit MouseCaptureModule(Broker *const broker)
            : Module("MouseCaptureModule"),
              mBroker(broker) {}

protected:
    bool executeIteration() override;

    void yieldIteration() override;

private:
    Broker *const mBroker;
    bool mRan = false;
};


#endif //CELLSINTERLINKED_MOUSECAPTUREMODULE_H
