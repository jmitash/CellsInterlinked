
#include "logging/LogHelper.h"
#include "meta/BuildInfo.h"
#include "message/TestSubscriber.h"

int main() {
    spdlog::logger logger = LogHelper::logger(__FILE__);
    logger.info("Starting {} {} ({})", BuildInfo::projectName, BuildInfo::projectVersion, BuildInfo::buildType);

    return 0;
}
