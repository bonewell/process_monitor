#include "process.h"

#include "loop.h"
#include "memory_listener.h"
#include "proc_reader.h"

Process::Process(int pid, Loop& loop)
    : pid_{pid},
      loop_{loop}
{
    thread_ = std::thread{&Process::Run, this};
}

Process::~Process()
{
    running_ = false;
    thread_.join();
}

void Process::Run()
{
    constexpr auto timeout = std::chrono::milliseconds(500);

//    ProcMemory m;
    running_ = true;
    while (running_) {

        std::this_thread::sleep_for(timeout);
    }
}
