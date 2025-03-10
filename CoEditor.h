
#ifndef COEDITOR_H
#define COEDITOR_H

#include "BoundedBuffer.h"
#include <thread>
#include <chrono>
#include <iostream>

class CoEditor {
public:
    // Constructor that initializes the dispatcher and screen queues
    CoEditor(BoundedBuffer& dispatcherQueue, BoundedBuffer& screenQueue);

    // Edits the items in the dispatcher queue and inserts them into the screen queue
    void edit();

private:
    BoundedBuffer& dispatcherQueue; // Dispatcher queue's reference
    BoundedBuffer& screenQueue; // Screen queue's reference
};

#endif // COEDITOR_H
