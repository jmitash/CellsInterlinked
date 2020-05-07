
#include "monitor/MonitorDiscoveryModule.h"

bool MonitorDiscoveryModule::executeIteration() {
    auto monitors = mMonitorDiscoverer->discoverAll();

    if (mMonitorStateManager.isDifferentState(monitors)) {
        mMonitorStateManager.handleStateChange(monitors);
    }

    return false;
}

void MonitorDiscoveryModule::yieldIteration() {
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
}
