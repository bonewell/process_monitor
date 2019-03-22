#ifndef MONITOR_MOCK_PROCESS_TABLE_H
#define MONITOR_MOCK_PROCESS_TABLE_H

#include "gmock/gmock.h"
#include "general/process_table.h"

namespace general {

class Memory;

class MockProcessTable : public ProcessTable {
public:
    MOCK_METHOD0(HasNext, bool());
    MOCK_METHOD0(Next, ProcessInfo());
    MOCK_METHOD0(Rewind, void());
    MOCK_METHOD1(GetMemory, std::unique_ptr<Memory>(const ProcessInfo& info));
};

}  // namespace general

#endif // MONITOR_MOCK_PROCESS_TABLE_H
