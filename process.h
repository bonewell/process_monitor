#ifndef PROCESS_H
#define PROCESS_H

#include <atomic>
#include <thread>

class Loop;

class Process
{
public:
    Process(int pid, Loop& loop);
    ~Process();

private:
    void Run();
    int pid_;
    Loop& loop_;
    std::atomic_bool running_{false};
    std::thread thread_;
};

#endif // PROCESS_H
