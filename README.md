# Concurrent Programming and Synchronization 🚦

## Overview 📰
This project simulates a concurrent news broadcasting system to demonstrate synchronization mechanisms and inter-thread communication. It is built in C++ using threads, bounded buffers, semaphores, and mutexes to illustrate concurrent programming concepts.

## Features 📋
- **Producers 🛠️:** Generate categorized news messages (`SPORTS`, `NEWS`, `WEATHER`).
- **Dispatcher 📡:** Routes news messages from producers to appropriate editor queues.
- **Co-Editors ✏️:** Simulate editing with delays and forward messages to the screen manager.
- **Screen Manager 🖥️:** Displays edited messages and indicates system completion.

## Project Structure 📂
```
.
├── BoundedBuffer.cpp
├── BoundedBuffer.h
├── CountingSemaphore.h
├── Producer.cpp
├── Producer.h
├── Dispatcher.cpp
├── Dispatcher.h
├── CoEditor.cpp
├── CoEditor.h
├── ScreenManager.cpp
├── ScreenManager.h
├── main.cpp
├── Makefile
└── config.txt
```

## Components 🧩

### Producer 🛠️
- Generates news strings and signals completion (`DONE`).

### Dispatcher 📡
- Checks producer queues in a Round Robin fashion.
- Categorizes messages into sports, news, and weather queues.
- Signals completion with `DONE` messages.

### Co-Editors ✏️
- Simulate editing with a short delay (0.1 seconds).
- Forward edited news to a shared queue for the Screen Manager.
- Immediately forward `DONE` signals.

### Screen Manager 🖥️
- Displays messages and indicates system completion with a final `DONE` message.

## Bounded Buffer 🔒
- Thread-safe implementation using mutexes and semaphores.
- Supports operations: `insert`, `remove`, and `front`.

## Counting Semaphore 🧮
- Controls synchronization using condition variables for thread-safe waiting and signaling.

## Configuration File ⚙️
Structure your configuration like this:
```
PRODUCER 1
30
queue size = 5

PRODUCER 2
25
queue size = 3

PRODUCER 3
16
queue size = 30

Co-Editor queue size = 17
```


## Contributors 👨‍💻
- Michael Landesman Nir
- Lior Muallem

