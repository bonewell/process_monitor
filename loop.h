#ifndef LOOP_H
#define LOOP_H

#include <atomic>
#include <memory>
#include <thread>
#include <unordered_map>

#include "memory.h"
#include "memory_listener.h"
#include "process.h"
#include "status_listener.h"

class StatusMonitor;

class Loop : public StatusListener, public MemoryListener
{
public:
    explicit Loop(StatusMonitor& monitor);
    ~Loop() override;
    void OnStarted(const ProcessInfo& info) override;
    void OnFinished(const ProcessInfo& info) override;
    void OnMemoryChanged(int pid, long long) override;
    std::unique_ptr<Memory> GetMemory(int pid);

private:
    using Processes = std::unordered_map<int, std::unique_ptr<Process>>;
    void Run();
    StatusMonitor& monitor_;
    std::atomic_bool running_{false};
    std::thread thread_;
    Processes ps_;
};

#endif // LOOP_H
