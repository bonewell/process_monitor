#ifndef PROC_MEMORY_H
#define PROC_MEMORY_H

#include <fstream>

#include "memory.h"

class ProcMemory : public Memory
{
public:
    explicit ProcMemory(int pid);
    ~ProcMemory() override;
    long long Total() override;

private:
    std::ifstream ifs_;
};

#endif // PROC_MEMORY_H
