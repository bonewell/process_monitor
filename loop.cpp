#include "loop.h"

#include "logger.h"
#include "memory_monitor.h"
#include "status_monitor.h"
#include "process_table.h"

static LOGGER_INSTANCE("Process");

Loop::Loop(StatusMonitor& monitor)
    : monitor_{monitor},
      thread_{&Loop::Run, this}
{
}

Loop::~Loop()
{
    running_ = false;
    thread_.join();
    ps_.clear();
}

void Loop::Run()
{
    constexpr auto timeout = std::chrono::milliseconds(500);

    running_ = true;
    monitor_.Subscribe(this);
    while (running_) {
        monitor_.Scan();
        std::this_thread::sleep_for(timeout);
    }
    monitor_.Unsubscribe(this);
}

void Loop::OnStarted(int pid)
{
    constexpr auto name = "<name>";
    LOGGER_INFO(name << " (" << pid << "): started");
    ps_.emplace(pid, std::unique_ptr<Process>{new Process{pid, *this}});
}

void Loop::OnFinished(int pid)
{
    constexpr auto name = "<name>";
    LOGGER_INFO(name << " (" << pid << "): finished");
    ps_.erase(pid);
}

void Loop::OnMemoryChanged(int pid, long long value)
{
    constexpr auto name = "<name>";
    LOGGER_INFO(name << " (" << pid << "): memory changed " << value);
}

std::unique_ptr<Memory> Loop::GetMemory(int pid)
{
    return monitor_.GetMemory(pid);
}
