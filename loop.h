#ifndef LOOP_H
#define LOOP_H

#include <atomic>
#include <memory>
#include <thread>
#include <unordered_map>

#include "general/memory.h"
#include "monitor/memory_listener.h"
#include "monitor/status_listener.h"
#include "process.h"

class StatusMonitor;

class Loop : public StatusListener, public MemoryListener
{
public:
    explicit Loop(StatusMonitor& monitor);
    ~Loop();
    void OnStarted(const ProcessInfo& info) override;
    void OnFinished(const ProcessInfo& info) override;
    void OnMemoryChanged(const ProcessInfo& info, long long value) override;
    std::unique_ptr<Memory> GetMemory(const ProcessInfo& info);

private:
    using Processes = std::unordered_map<int, std::unique_ptr<Process>>;
    void Run();
    StatusMonitor& monitor_;
    std::atomic_bool running_{false};
    std::thread thread_;
    Processes ps_;
};

#endif // LOOP_H
