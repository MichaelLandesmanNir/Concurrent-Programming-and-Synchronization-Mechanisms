
#ifndef SCREENMANAGER_H
#define SCREENMANAGER_H

#include "BoundedBuffer.h"
#include <iostream>
#include <chrono>

class ScreenManager {
public:
    // Constructor that initializes the screen queue
    ScreenManager(BoundedBuffer& screenQueue);

    // Displays the items in the screen queue
    void display();

private:
    BoundedBuffer& screenQueue;
};

#endif // SCREENMANAGER_H
