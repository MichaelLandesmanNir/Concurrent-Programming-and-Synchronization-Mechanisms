
#include "Dispatcher.h"

// Constructor that initializes the producer queues and the sports, news, and weather queues
Dispatcher::Dispatcher(const vector<BoundedBuffer*>& producerQueues,
                       BoundedBuffer& sportsQueue,
                       BoundedBuffer& newsQueue,
                       BoundedBuffer& weatherQueue)
    : producerQueues(producerQueues), sportsQueue(sportsQueue), newsQueue(newsQueue), weatherQueue(weatherQueue) {}


// Dispatches the items from the producer queues to the sports, news, and weather queues
void Dispatcher::dispatch() {
    int numDoneProducers = 0;
    while (numDoneProducers < producerQueues.size()) {
        for (auto& queue : producerQueues) {

            // If the producer queue is not empty
            if(queue->size() > 0) {
                // Peek at the front item
                string item = queue->front();
                if (item == "DONE") {
                    queue->remove();
                    numDoneProducers++;
                } else {
                    // Determine type and route to appropriate queue
                    // First, split the item into tokens
                    istringstream iss(item);
                    vector<string> tokens;
                    string token;
                    
                    while (iss >> token) {
                        tokens.push_back(token);
                    }

                    // If the item has at least 3 tokens
                    if (tokens.size() >= 3) {
                        string typeStr = tokens[2];

                        // Checking the type of the item (news)
                        if (typeStr == "SPORTS") {
                            // If the sports queue is not full
                            if(sportsQueue.size() < sportsQueue.getMaxSize()) {
                                sportsQueue.insert(item);
                                queue->remove();
                            }
                        } else if (typeStr == "NEWS") {
                            // If the news queue is not full
                            if(newsQueue.size() < newsQueue.getMaxSize()){
                                newsQueue.insert(item);
                                queue->remove();
                            }
                        } else if (typeStr == "WEATHER") {
                            // If the weather queue is not full
                            if(weatherQueue.size() < weatherQueue.getMaxSize()) {
                                weatherQueue.insert(item);
                                queue->remove();
                            }
                        }
                    }
                }
            }
        }
    }

    // Signal the end to co-editors
    sportsQueue.insert("DONE");
    newsQueue.insert("DONE");
    weatherQueue.insert("DONE");
}
