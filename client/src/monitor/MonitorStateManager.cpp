
#include "monitor/MonitorStateManager.h"
#include "monitor/MonitorStateChangeEvent.h"
#include "util/StringUtil.h"

bool MonitorStateManager::isDifferentState(const std::set<Monitor> &newState) const {
    auto different = mCurrentState != newState;

    if (different && logger.should_log(spdlog::level::debug)) {
        logger.trace("Old monitor state: {}",
                     StringUtil::toString(mCurrentState, [](const Monitor &m) { return m.toString(); }));
        logger.debug("New monitor state: {}",
                     StringUtil::toString(newState, [](const Monitor &m) { return m.toString(); }));
    } else {
        logger.trace("No monitor state change detected");
    }

    return different;
}

void MonitorStateManager::handleStateChange(const std::set<Monitor> &newState) {
    mCurrentState = newState;

    logger.info("Monitor state change detected");
    mBroker->publish(std::make_shared<MonitorStateChangeEvent>(newState));
}
