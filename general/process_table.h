#ifndef GENERAL_PROCESS_TABLE_H
#define GENERAL_PROCESS_TABLE_H

#include <memory>
#include <string>
#include "process_info.h"

namespace general {

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

}  // namespace general

#endif  // GENERAL_PROCESS_TABLE_H
