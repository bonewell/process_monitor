#ifndef PROC_READER_H
#define PROC_READER_H

#include <memory>
#include <dirent.h>
#include "process_table.h"

class Memory;

class ProcReader : public ProcessTable
{
public:
    explicit ProcReader();
    ~ProcReader() override;
    bool HasNext() override;
    ProcessInfo Next() override;
    void Rewind() override;
    std::unique_ptr<Memory> GetMemory(int pid) override;

private:
    std::string GetName(const std::string& pid) const;
    DIR* dirp_{nullptr};
    std::string current_pid_;
};

#endif // PROC_READER_H
