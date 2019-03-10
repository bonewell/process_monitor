#ifndef PROCESS_TABLE_H
#define PROCESS_TABLE_H

#include <memory>
#include <string>
#include "process_info.h"

class Memory;

class ProcessTable
{
public:
    virtual bool HasNext() = 0;
    virtual ProcessInfo Next() = 0;
    virtual void Rewind() = 0;
    virtual std::unique_ptr<Memory> GetMemory(const ProcessInfo& info) = 0;
    virtual ~ProcessTable() = default;
};

#endif // PROCESS_TABLE_H
