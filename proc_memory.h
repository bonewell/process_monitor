#ifndef PROC_MEMORY_H
#define PROC_MEMORY_H

#include <fstream>

#include "memory.h"
#include "process_info.h"

class ProcMemory : public Memory
{
public:
    explicit ProcMemory(ProcessInfo info);
    ~ProcMemory() override;
    const ProcessInfo& Info() const override;
    long long Total() override;

private:
    ProcessInfo info_;
    std::ifstream ifs_;
};

#endif // PROC_MEMORY_H
