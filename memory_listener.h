#ifndef MEMORY_LISTENER_H
#define MEMORY_LISTENER_H

class MemoryListener {
public:
    virtual void OnMemoryChanged(int pid, long long) = 0;
    virtual ~MemoryListener() = default;
};

#endif // MEMORY_LISTENER_H
