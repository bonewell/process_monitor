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

void Loop::OnStarted(const ProcessInfo& info)
{
    LOGGER_INFO(info.name << " (" << info.pid << "): started");
    ps_.emplace(info.pid, std::unique_ptr<Process>{new Process{info, *this}});
}

void Loop::OnFinished(const ProcessInfo& info)
{
    LOGGER_INFO(info.name << " (" << info.pid << "): finished");
    ps_.erase(info.pid);
}

void Loop::OnMemoryChanged(const ProcessInfo& info, long long value)
{
    LOGGER_INFO(info.name << " (" << info.pid << "): memory changed " << value);
}

std::unique_ptr<Memory> Loop::GetMemory(const ProcessInfo& info)
{
    return monitor_.GetMemory(info);
}
