#ifndef PROC_PROC_READER_H
#define PROC_PROC_READER_H

#include <memory>
#include <dirent.h>
#include "general/process_table.h"

class Memory;

namespace proc {

class ProcReader : public general::ProcessTable
{
public:
    explicit ProcReader();
    ~ProcReader();
    bool HasNext() override;
    general::ProcessInfo Next() override;
    void Rewind() override;
    std::unique_ptr<general::Memory> GetMemory(const general::ProcessInfo& info) override;

private:
    std::string GetName(const std::string& pid) const;
    DIR* dirp_{nullptr};
    std::string current_pid_;
};

}  // namespace proc

#endif  // PROC_PROC_READER_H
