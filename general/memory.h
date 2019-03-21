#ifndef GENERAL_MEMORY_H
#define GENERAL_MEMORY_H

namespace general {

struct ProcessInfo;

class Memory {
public:
    virtual const ProcessInfo& Info() const = 0;
    virtual long long Total() = 0;
    virtual ~Memory() = default;
};

}  // namespace general

#endif  // GENERAL_MEMORY_H
