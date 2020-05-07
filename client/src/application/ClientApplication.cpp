
#include "application/ClientApplication.h"

void ClientApplication::run() {
    logger.debug("ClientApplication run");

    for (auto module : mAllModules) {
        module->start();
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(1000000000));
}
