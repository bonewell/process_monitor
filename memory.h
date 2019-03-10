#ifndef MEMORY_H
#define MEMORY_H

struct ProcessInfo;

class Memory {
public:
    virtual const ProcessInfo& Info() const = 0;
    virtual long long Total() = 0;
    virtual ~Memory() = default;
};

#endif // MEMORY_H
