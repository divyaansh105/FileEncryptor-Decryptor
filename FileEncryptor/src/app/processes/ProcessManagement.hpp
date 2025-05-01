#pragma once

#include <windows.h>
#include <memory>
#include <atomic>
#include <mutex>
#include <string>

#include "Task.hpp"

// Shared memory structure definition
struct SharedMemory {
    std::atomic<int> size;
    char tasks[1000][256];
    int front;
    int rear;
};

class ProcessManagement {
public:
    ProcessManagement();
    ~ProcessManagement();

    bool addTask(std::unique_ptr<Task> task);
    void executeTask();

private:
   
    HANDLE itemsSemaphore = nullptr;
    HANDLE emptySlotsSemaphore = nullptr;

    HANDLE hMapFile = nullptr;
    SharedMemory* sharedMem = nullptr;

    std::mutex queueLock;

    const std::string SHM_NAME = "Global\\my_queue";
};
