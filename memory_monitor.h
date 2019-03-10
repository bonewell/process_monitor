#ifndef MEMORY_MONITOR_H
#define MEMORY_MONITOR_H

#include <memory>
#include <unordered_set>

class Memory;
class MemoryListener;

class MemoryMonitor
{
public:
    using Listeners = std::unordered_set<MemoryListener*>;

    MemoryMonitor(std::unique_ptr<Memory> memory, int pid);
    ~MemoryMonitor();
    void Subscribe(MemoryListener* listener);
    void Unsubscribe(MemoryListener* listener);
    void Measure();

private:
    inline void Notify() const;
    std::unique_ptr<Memory> memory_;
    int pid_;
    Listeners listeners_;
    long long total_{0};
};

#endif // MEMORY_MONITOR_H
