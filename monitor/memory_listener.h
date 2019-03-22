#ifndef MONITOR_MEMORY_LISTENER_H
#define MONITOR_MEMORY_LISTENER_H

namespace general {
struct ProcessInfo;
}  // namespace general

namespace monitor {

class MemoryListener {
public:
    virtual void OnMemoryChanged(const general::ProcessInfo& info, long long value) = 0;
    virtual ~MemoryListener() = default;
};

}  // namespace monitor

#endif  // MONITOR_MEMORY_LISTENER_H
