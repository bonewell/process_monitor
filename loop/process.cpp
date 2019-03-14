#include "process.h"

#include "loop.h"
#include "monitor/memory_monitor.h"
#include "proc/proc_reader.h"

Process::Process(const ProcessInfo& info, Loop& loop)
    : info_{info},
      loop_{loop},
      thread_{&Process::Run, this}
{
}

Process::~Process()
{
    running_ = false;
    thread_.join();
}

void Process::Run()
{
    constexpr auto timeout = std::chrono::milliseconds(500);

    MemoryMonitor monitor{loop_.GetMemory(info_)};
    running_ = true;
    monitor.Subscribe(&loop_);
    while (running_) {
        monitor.Measure();
        std::this_thread::sleep_for(timeout);
    }
    monitor.Unsubscribe(&loop_);
}
