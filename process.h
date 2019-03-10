#ifndef PROCESS_H
#define PROCESS_H

#include <atomic>
#include <thread>

#include "process_info.h"

class Loop;
class MemoryMonitor;

class Process
{
public:
    Process(const ProcessInfo& info, Loop& loop);
    ~Process();

private:
    void Run();
    ProcessInfo info_;
    Loop& loop_;
    std::atomic_bool running_{false};
    std::thread thread_;
};

#endif // PROCESS_H
