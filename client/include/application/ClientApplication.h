
#ifndef CELLSINTERLINKED_CLIENTAPPLICATION_H
#define CELLSINTERLINKED_CLIENTAPPLICATION_H

#include "logging/LogHelper.h"

/**
 * The client application. Serves as a starting point for initializing and running the application.
 */
class ClientApplication {
public:
    /**
     * Runs the application.
     */
    void run();

private:
    inline static auto logger = LogHelper::logger(__FILE__);
};


#endif //CELLSINTERLINKED_CLIENTAPPLICATION_H
