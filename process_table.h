#ifndef PROCESS_TABLE_H
#define PROCESS_TABLE_H

#include <memory>
#include <string>

class Memory;

struct ProcessInfo {
    int pid;
    std::string name;
};

class ProcessTable
{
public:
    virtual bool HasNext() = 0;
    virtual ProcessInfo Next() = 0;
    virtual void Rewind() = 0;
    virtual std::unique_ptr<Memory> GetMemory(int pid) = 0;
    virtual ~ProcessTable() = default;
};

#endif // PROCESS_TABLE_H
