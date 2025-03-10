#ifndef DISPATCHER_H
#define DISPATCHER_H

#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include "BoundedBuffer.h"

class Dispatcher {
public:
    // Constructor that initializes the producer queues and the sports, news, and weather queues
    Dispatcher(const vector<BoundedBuffer*>& producerQueues,
               BoundedBuffer& sportsQueue,
               BoundedBuffer& newsQueue,
               BoundedBuffer& weatherQueue);

    // Dispatches the items from the producer queues to the sports, news, and weather queues
    void dispatch();

private:
    vector<BoundedBuffer*> producerQueues;  // Contains references to the producer queues

    BoundedBuffer& sportsQueue; // Co-Editor queue for sports
    BoundedBuffer& newsQueue;   // Co-Editor queue for news
    BoundedBuffer& weatherQueue; // Co-Editor queue for weather
};

#endif // DISPATCHER_H
