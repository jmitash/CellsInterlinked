#include <iostream>
#include "meta/BuildInfo.h"

int main() {
    std::cout << "Starting " << PROJECT_NAME << " " << PROJECT_VERSION << " (" << PROJECT_BUILD_TYPE << ")" << std::endl;
    return 0;
}
