#include "memory_monitor.h"

#include <algorithm>
#include <cstdlib>

#include "memory.h"
#include "memory_listener.h"

namespace {
const auto kMemoryLimit = 1000000;  // bytes
}  // namespace

MemoryMonitor::MemoryMonitor(Memory& memory, int pid)
    : memory_{memory},
      pid_{pid}
{
}

void MemoryMonitor::Subscribe(MemoryListener* listener)
{
    listeners_.insert(listener);
}

void MemoryMonitor::Unsubscribe(MemoryListener* listener)
{
    listeners_.erase(listener);
}

void MemoryMonitor::Measure()
{
    auto total = memory_.Total();
    if (abs(total - total_) > kMemoryLimit) {
        total_ = total;
        Notify();
    }
}

void MemoryMonitor::Notify() const
{
    std::for_each(std::begin(listeners_), std::end(listeners_),
                  [this](MemoryListener* l) {
        l->OnMemoryChanged(pid_, total_);
    });
}
