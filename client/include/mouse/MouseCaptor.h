
#ifndef CELLSINTERLINKED_MOUSECAPTOR_H
#define CELLSINTERLINKED_MOUSECAPTOR_H

/**
 * A captor for the mice on the system. Captures mouse movement, button presses, scrolling, etc.
 */
class MouseCaptor {
public:
    /**
     * Starts a loop to listen to and capture mouse events.
     */
    virtual void run() = 0;

};

#endif //CELLSINTERLINKED_MOUSECAPTOR_H
