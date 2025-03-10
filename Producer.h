
#ifndef PRODUCER_H
#define PRODUCER_H

#include "BoundedBuffer.h"
#include <string>
#include <unordered_map>
#include <vector>
#include <random>
#include <iostream>
#include <queue>

// Enumerated type for the news type
enum NewsType { SPORTS, NEWS, WEATHER };

class Producer {
public:
    // Constructor that initializes the producer's id, number of products, and the queue
    Producer(int id, int numProducts, BoundedBuffer& queue);

    // Produces the items and inserts them into the queue
    void produce();


private:
    int id; // Producer's id
    int numProducts;    // Number of products to produce
    BoundedBuffer& queue;   // Producer's queue
    vector<NewsType> types; // Vector of news types
    unordered_map<NewsType, int> typeCounters;  // Map of news type counters
    string newsTypeToString(NewsType type); // Converts the news type to a string

    // Returns a random news type
    NewsType getRandomType();
};

#endif // PRODUCER_H
