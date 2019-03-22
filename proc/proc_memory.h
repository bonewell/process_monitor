#ifndef PROC_PROC_MEMORY_H
#define PROC_PROC_MEMORY_H

#include <fstream>

#include "general/memory.h"
#include "general/process_info.h"

namespace proc {

class ProcMemory : public general::Memory
{
public:
    explicit ProcMemory(const general::ProcessInfo& info);
    ~ProcMemory();
    const general::ProcessInfo& Info() const override;
    long long Total() override;

private:
    general::ProcessInfo info_;
    std::ifstream ifs_;
};

}  // namespace proc

#endif  // PROC_PROC_MEMORY_H
