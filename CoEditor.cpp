

#include "CoEditor.h"

CoEditor::CoEditor(BoundedBuffer& dispatcherQueue, BoundedBuffer& screenQueue)
    : dispatcherQueue(dispatcherQueue), screenQueue(screenQueue) {}

void CoEditor::edit() {
    while (true) {
        // If dispatcher queue is not empty and screen queue is not full
        // Extract an item (news) from the dispatcher queue and insert it into the screen queue
        if(dispatcherQueue.size() > 0) {
            if(screenQueue.size() < screenQueue.getMaxSize()) {
                string item = dispatcherQueue.remove();
                // If the item corresponds to "DONE", insert it into the screen queue and break the loop
                if (item == "DONE") {
                    screenQueue.insert("DONE");
                    break;
                }
                this_thread::sleep_for(chrono::milliseconds(100)); // Simulate editing done by Co-Editors
                screenQueue.insert(item);
            }
        }
    }
}
