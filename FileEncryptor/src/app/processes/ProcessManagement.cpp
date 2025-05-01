#include <iostream>
#include <windows.h>
#include <memory>
#include <mutex>
#include <string>
#include <thread>
#include <atomic>

#include "ProcessManagement.hpp"
#include "../encryptDecrypt/Cryption.hpp"

ProcessManagement::ProcessManagement()
{

    itemsSemaphore = CreateSemaphoreA(nullptr, 0, 1000, "Global\\items_semaphore");
    emptySlotsSemaphore = CreateSemaphoreA(nullptr, 1000, 1000, "Global\\empty_slots_semaphore");

    // Create shared memory using a named file mapping
    hMapFile = OpenFileMappingA(FILE_MAP_ALL_ACCESS, FALSE, SHM_NAME.c_str());

    if (!hMapFile)
    {
        // If the shared memory doesn't exist, create it
        hMapFile = CreateFileMappingA(
            INVALID_HANDLE_VALUE, //  system paging file
            nullptr,              // Default security
            PAGE_READWRITE,       // Access mode
            0,                    // Max size high-order DWORD
            sizeof(SharedMemory), // Max size low-order DWORD
            SHM_NAME.c_str()      // Shared memory name
        );

        if (!hMapFile)
        {
            // Error handling: Format and print error
            DWORD errorCode = GetLastError();
            LPVOID lpMsgBuf;
            FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                           nullptr, errorCode, 0, (LPSTR)&lpMsgBuf, 0, nullptr);
            std::cerr << "CreateFileMappingA failed with error " << errorCode << ": " << (char *)lpMsgBuf << std::endl;
            LocalFree(lpMsgBuf);
            return; 
        }
    }

    sharedMem = static_cast<SharedMemory *>(MapViewOfFile(hMapFile, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(SharedMemory)));

    if (sharedMem == nullptr)
    {
        std::cerr << "Error mapping view of file: " << GetLastError() << std::endl;
        CloseHandle(hMapFile);
        return;
    }

    sharedMem->front = 0;
    sharedMem->rear = 0;
    sharedMem->size.store(0);
}

ProcessManagement::~ProcessManagement()
{

    if (sharedMem != nullptr)
    {
        UnmapViewOfFile(sharedMem);
        sharedMem = nullptr;
    }

    if (hMapFile != nullptr)
    {
        CloseHandle(hMapFile);
        hMapFile = nullptr;
    }

    // Close the semaphores
    if (itemsSemaphore != nullptr)
    {
        CloseHandle(itemsSemaphore);
        itemsSemaphore = nullptr;
    }
    if (emptySlotsSemaphore != nullptr)
    {
        CloseHandle(emptySlotsSemaphore);
        emptySlotsSemaphore = nullptr;
    }
}


bool ProcessManagement::addTask(std::unique_ptr<Task> task) {
    // Wait for an empty slot in the queue (equivalent to sem_wait in POSIX)
    WaitForSingleObject(emptySlotsSemaphore, INFINITE);

    std::unique_lock<std::mutex> lock(queueLock);

    if (sharedMem->size.load() >= 1000) {
        return false;
    }

    // Add the task to shared memory
    strcpy(sharedMem->tasks[sharedMem->rear], task->toString().c_str());
    sharedMem->rear = (sharedMem->rear + 1) % 1000;
    sharedMem->size.fetch_add(1);

    // Unlock the mutex after modifying shared memory
    lock.unlock();

    // Signal that a new item is available (equivalent to sem_post in POSIX)
    ReleaseSemaphore(itemsSemaphore, 1, nullptr);

    // Start a new thread to execute the task
    std::thread taskThread(&ProcessManagement::executeTask, this);
    taskThread.detach();  // Detach the thread so it runs independently

    return true;
}
void ProcessManagement::executeTask()
{
    // Wait until an item is available
    WaitForSingleObject(itemsSemaphore, INFINITE);

    std::unique_lock<std::mutex> lock(queueLock);

    char taskStr[256];
    strcpy_s(taskStr, sharedMem->tasks[sharedMem->front]);
    sharedMem->front = (sharedMem->front + 1) % 1000;
    sharedMem->size.fetch_sub(1);

    lock.unlock();

    ReleaseSemaphore(emptySlotsSemaphore, 1, nullptr);

    executeCryption(taskStr);
}
