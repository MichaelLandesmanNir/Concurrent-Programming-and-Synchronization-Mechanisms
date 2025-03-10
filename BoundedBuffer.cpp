

#include "BoundedBuffer.h"

BoundedBuffer::BoundedBuffer(int size) 
    : maxSize(size), items(0), spaces(size) {}

string BoundedBuffer::front() {
    unique_lock<mutex> lock(mtx);  // Lock the buffer to read front (making it thread safe)
    return buffer.front();  // Return the front item
}

void BoundedBuffer::insert(const string& item) {
    spaces.wait();  // Wait for space to become available
    {
        unique_lock<mutex> lock(mtx);  // Lock the buffer for modification
        buffer.push(item);  // Insert the item
    }
    items.signal();  // Signal that a new item is available
}

string BoundedBuffer::remove() {
    items.wait();  // Wait for an item to become available
    string item;
    {
        unique_lock<mutex> lock(mtx);  // Lock the buffer for modification
        item = buffer.front();  // Get the item
        buffer.pop();  // Remove the item
    }
    spaces.signal();  // Signal that a space is now available
    return item;  // Return the item
}

int BoundedBuffer::size() const {
    unique_lock<mutex> lock(mtx);  // Lock the buffer to read size (making it thread safe)
    return buffer.size();  // Return the size
}
