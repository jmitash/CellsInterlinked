
#ifndef CELLSINTERLINKED_MOUSECAPTORFACTORY_H
#define CELLSINTERLINKED_MOUSECAPTORFACTORY_H

#include <memory>
#include "mouse/MouseCaptor.h"

/**
 * Factory to provide an instance of a MouseCaptor. This factory is meant to hide the OS-specific implementation of mouse captors.
 */
class MouseCaptorFactory {
public:
    /**
     * Generates an OS-specific mouse captor.
     * @return a pointer to a mouse captor
     */
    [[nodiscard]] std::unique_ptr<MouseCaptor> getMouseCaptor();

};


#endif //CELLSINTERLINKED_MOUSECAPTORFACTORY_H
