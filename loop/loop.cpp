#include "loop.h"

#include "general/process_table.h"
#include "monitor/memory_monitor.h"
#include "monitor/status_monitor.h"
#include "utils/logger.h"

static LOGGER_INSTANCE("Process");

namespace loop {

Loop::Loop(monitor::StatusMonitor& monitor)
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

void Loop::OnStarted(const general::ProcessInfo& info)
{
    LOGGER_INFO(info.name << " (" << info.pid << "): started");
    ps_.emplace(info.pid, std::unique_ptr<Process>{new loop::Process{info, *this}});
}

void Loop::OnFinished(const general::ProcessInfo& info)
{
    LOGGER_INFO(info.name << " (" << info.pid << "): finished");
    ps_.erase(info.pid);
}

void Loop::OnMemoryChanged(const general::ProcessInfo& info, long long value)
{
    LOGGER_INFO(info.name << " (" << info.pid << "): memory changed " << value);
}

std::unique_ptr<general::Memory> Loop::GetMemory(const general::ProcessInfo& info)
{
    return monitor_.GetMemory(info);
}

}  // namespace loop
