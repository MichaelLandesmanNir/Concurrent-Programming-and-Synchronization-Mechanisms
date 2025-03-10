
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdexcept>
#include <thread>
#include "Producer.h"
#include "Dispatcher.h"
#include "CoEditor.h"
#include "ScreenManager.h"
#include "BoundedBuffer.h"

using namespace std;

// g++ -o ex3.out main.cpp Producer.cpp Dispatcher.cpp CoEditor.cpp ScreenManager.cpp BoundedBuffer.cpp
// ./ex3.out config.txt

struct Configuration {
    struct ProducerConfig {
        int id;
        int numProducts;
        int queueSize;
    };
    vector<ProducerConfig> producers;
    int coEditorQueueSize;
};

Configuration parseConfigFile(const string& filename) {
    Configuration config;
    ifstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Unable to open configuration file.");
    }

    string line;
    int currentProducerId = 0;
    while (getline(file, line)) {
        if (line.find("PRODUCER") != string::npos) {
            currentProducerId++;
            Configuration::ProducerConfig prodConfig;
            prodConfig.id = currentProducerId;
            getline(file, line); // Read number of products
            prodConfig.numProducts = stoi(line);
            getline(file, line); // Read queue size
            size_t pos = line.find("=");
            if (pos != string::npos) {
                prodConfig.queueSize = stoi(line.substr(pos + 1));
            }
            config.producers.push_back(prodConfig);
        } else if (line.find("Co-Editor queue size") != string::npos) {
            size_t pos = line.find("=");
            if (pos != string::npos) {
                config.coEditorQueueSize = stoi(line.substr(pos + 1));
            }
        }
    }

    file.close();
    return config;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <config_file>" << endl;
        return 1;
    }

    string configFileName = argv[1];
    Configuration config;
    try {
        config = parseConfigFile(configFileName);
    } catch (exception& e) {
        cerr << "Error parsing configuration file: " << e.what() << endl;
        return 1;
    }

    // Initialize producers and their queues
    vector<Producer> producers;
    // Initialize producers and their queues
    vector<unique_ptr<BoundedBuffer>> producerQueues;
    for (const auto& prodConfig : config.producers) {
        // For the producer queue, add one extra space to allow for the "DONE" message
        auto queue = make_unique<BoundedBuffer>(prodConfig.queueSize);
        producerQueues.push_back(move(queue));
        Producer producer(prodConfig.id, prodConfig.numProducts, *producerQueues.back());
        producers.push_back(producer);
    }

    // Initialize co-editor queues
    BoundedBuffer sportsQueue(config.coEditorQueueSize);
    BoundedBuffer newsQueue(config.coEditorQueueSize);
    BoundedBuffer weatherQueue(config.coEditorQueueSize);

    // Initialize screen queue
    BoundedBuffer screenQueue(1000);

    // Initialize dispatcher with producer queues and co-editor queues
    vector<BoundedBuffer*> prodQueuesPtrs;
    for (auto& queue : producerQueues) {
        prodQueuesPtrs.push_back(queue.get());
    }
    Dispatcher dispatcher(prodQueuesPtrs, sportsQueue, newsQueue, weatherQueue);

    // Initialize co-editors and screen manager
    CoEditor sportsEditor(sportsQueue, screenQueue);
    CoEditor newsEditor(newsQueue, screenQueue);
    CoEditor weatherEditor(weatherQueue, screenQueue);
    ScreenManager screenManager(screenQueue);

    // Start producer threads
    vector<thread> producerThreads;
    for (auto& producer : producers) {
        producerThreads.emplace_back(&Producer::produce, &producer);
    }

    // Start dispatcher thread
    thread dispatcherThread(&Dispatcher::dispatch, &dispatcher);

    // Start co-editor threads
    thread sportsEditorThread(&CoEditor::edit, &sportsEditor);
    thread newsEditorThread(&CoEditor::edit, &newsEditor);
    thread weatherEditorThread(&CoEditor::edit, &weatherEditor);

    // Start screen manager thread
    thread screenManagerThread(&ScreenManager::display, &screenManager);

    // Join producer threads
    for (auto& thread : producerThreads) {
        thread.join();
    }

    // Join dispatcher thread
    dispatcherThread.join();

    // Join co-editor threads
    sportsEditorThread.join();
    newsEditorThread.join();
    weatherEditorThread.join();

    // Join screen manager thread
    screenManagerThread.join();

    return 0;
}
