
#include "../common/logging/LogHelper.h"
#include "meta/BuildInfo.h"

int main() {
    LogHelper::logger(__FILE__).info("Starting {} {} ({})", BuildInfo::projectName, BuildInfo::projectVersion,
                                     BuildInfo::buildType);
    return 0;
}
