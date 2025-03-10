
#include "Producer.h"

// Converts the news type to a string
string Producer::newsTypeToString(NewsType type) {
    switch(type) {
        case SPORTS: return "SPORTS";
        case NEWS: return "NEWS";
        case WEATHER: return "WEATHER";
        default: return "UNKNOWN";
    }
}

// Constructor that initializes the producer's id, number of products, and the queue
Producer::Producer(int id, int numProducts, BoundedBuffer& queue) 
    : id(id), numProducts(numProducts), queue(queue), types{SPORTS, NEWS, WEATHER} {
    typeCounters[SPORTS] = 0;
    typeCounters[NEWS] = 0;
    typeCounters[WEATHER] = 0;
}

// Returns a random news type
NewsType Producer::getRandomType() {
    // Random number generator
    static random_device rd;
    // Mersenne Twister random number generator
    static mt19937 gen(rd());
    // Uniform distribution of integers
    uniform_int_distribution<> dis(0, types.size() - 1);
    return types[dis(gen)];
}

void Producer::produce() {
    int produced = 0;

    while (produced < numProducts) {
        // Add item to the queue, blocking if the queue is full
        // if items can be added
        if(queue.size() < queue.getMaxSize()) {
            NewsType type = getRandomType();
            int count = typeCounters[type]++;
            string news = "Producer " + to_string(id) + " " + newsTypeToString(type) + " " + to_string(count);

            produced++;
            // cout << news << " Produced: " << produced << endl;
            queue.insert(news);
        }
    }

    // Signal the end of production by adding "DONE" to the queue
    queue.insert("DONE");
}

