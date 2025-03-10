
#include "ScreenManager.h"

ScreenManager::ScreenManager(BoundedBuffer& screenQueue)
    : screenQueue(screenQueue) {}

void ScreenManager::display() {
    // There are three "DONE" items to be received from the screen queue
    // 3-CoEditors * 1-DONE each = 3-DONE items
    // NEWS: 3, SPORTS: 3, WEATHER: 3

    int count = 0;

    while (true) {
        if(screenQueue.size() > 0) {
            std::string item = screenQueue.remove();
            if (item == "DONE") {
                count++;
            }
            else{
                std::cout << item << std::endl;
            }
        }
        // If all the "DONE" items have been received, break the loop
        if(count == 3) {
            std::cout << "DONE" << std::endl;
            break;
        }
    }
}
