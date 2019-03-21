#ifndef LOOP_LOOP_H
#define LOOP_LOOP_H

#include <atomic>
#include <memory>
#include <thread>
#include <unordered_map>

#include "general/memory.h"
#include "monitor/memory_listener.h"
#include "monitor/status_listener.h"
#include "process.h"

namespace monitor {
class StatusMonitor;
}  // namespace monitor

namespace loop {

class Loop : public monitor::StatusListener, public monitor::MemoryListener
{
public:
    explicit Loop(monitor::StatusMonitor& monitor);
    ~Loop();
    void OnStarted(const general::ProcessInfo& info) override;
    void OnFinished(const general::ProcessInfo& info) override;
    void OnMemoryChanged(const general::ProcessInfo& info, long long value) override;
    std::unique_ptr<general::Memory> GetMemory(const general::ProcessInfo& info);

private:
    using Processes = std::unordered_map<int, std::unique_ptr<Process>>;
    void Run();
    monitor::StatusMonitor& monitor_;
    std::atomic_bool running_{false};
    std::thread thread_;
    Processes ps_;
};

}  // namespace loop

#endif  // LOOP_LOOP_H
