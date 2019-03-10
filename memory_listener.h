#ifndef MEMORY_LISTENER_H
#define MEMORY_LISTENER_H

struct ProcessInfo;

class MemoryListener {
public:
    virtual void OnMemoryChanged(const ProcessInfo& info, long long value) = 0;
    virtual ~MemoryListener() = default;
};

#endif // MEMORY_LISTENER_H
