#include <iostream>
#include "meta/BuildInfo.h"

int main() {
    std::cout << "Starting " << BuildInfo::projectName << " " << BuildInfo::projectVersion << " (" << BuildInfo::buildType << ")" << std::endl;
    return 0;
}
