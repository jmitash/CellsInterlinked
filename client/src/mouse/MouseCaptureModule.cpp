
#include "mouse/MouseCaptureModule.h"

#include "mouse/MouseCaptorFactory.h"

bool MouseCaptureModule::executeIteration() {
    if (mRan) {
        return false;
    }

    mRan = true;
    MouseCaptorFactory mouseCaptorFactory;
    auto captor = mouseCaptorFactory.getMouseCaptor();
    captor->run();

    return false;
}

void MouseCaptureModule::yieldIteration() {
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}
