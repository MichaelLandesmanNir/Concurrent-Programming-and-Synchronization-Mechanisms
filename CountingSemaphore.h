#ifndef COUNTINGSEMAPHORE_H
#define COUNTINGSEMAPHORE_H

#include <mutex>
#include <condition_variable>

using namespace std;

class CountingSemaphore {
public:
    // Constructor that initializes the count
    CountingSemaphore(int initial) : count(initial) {}

    // Function that decrements the count and waits if the count is less than 0
    void wait() {
        unique_lock<mutex> lock(mtx);
        cv.wait(lock, [this]() { return count > 0; });
        --count;
    }

    // Function that increments the count and notifies the waiting threads
    void signal() {
        unique_lock<mutex> lock(mtx);
        ++count;
        cv.notify_one();
    }

private:
    int count;
    mutex mtx;
    condition_variable cv; // Conditional variable for waiting and notifying
};

#endif // COUNTINGSEMAPHORE_H
