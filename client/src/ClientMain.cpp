
#include "meta/BuildInfo.h"
#include "application/ClientApplication.h"

int main() {
    spdlog::logger logger = LogHelper::logger(__FILE__);
    logger.info("Starting {} {} ({})", BuildInfo::projectName, BuildInfo::projectVersion, BuildInfo::buildType);

    return 0;
}
