

#ifndef BOUNDEDBUFFER_H
#define BOUNDEDBUFFER_H

#include <queue>
#include <string>
#include <mutex>
#include "CountingSemaphore.h"

class BoundedBuffer {
public:
    // Constructor that initializes the buffer with a maximum size
    BoundedBuffer(int size);

    // Peeks the front item of the buffer
    string front();
    // Inserts an item into the buffer (thread-safe)
    void insert(const string& item);
    // Removes an item from the buffer (thread-safe)
    string remove();
    // Returns the current size of the buffer
    int size() const;
    // Returns the maximum size of the buffer
    int getMaxSize() const { return maxSize; }

private:
    int maxSize;
    mutable mutex mtx;       // Binary Semaphore
    queue<string> buffer;
    CountingSemaphore items; // Semaphore for available items
    CountingSemaphore spaces; // Semaphore for available spaces
};

#endif // BOUNDEDBUFFER_H
