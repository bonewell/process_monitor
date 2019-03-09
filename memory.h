#ifndef MEMORY_H
#define MEMORY_H

class Memory {
public:
    virtual long long Total() = 0;
    virtual ~Memory() = default;
};

#endif // MEMORY_H
