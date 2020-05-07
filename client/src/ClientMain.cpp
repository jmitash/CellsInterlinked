
#include "meta/BuildInfo.h"
#include "application/ClientApplication.h"

int main() {
    spdlog::logger logger = LogHelper::logger(__FILE__);
    logger.info("Starting {} {} ({})", BuildInfo::projectName, BuildInfo::projectVersion, BuildInfo::buildType);

    ClientApplication clientApplication;
    clientApplication.run();

    return 0;
}
