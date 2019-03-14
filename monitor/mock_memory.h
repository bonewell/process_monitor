#ifndef MOCK_MEMORY_H
#define MOCK_MEMORY_H

#include "gmock/gmock.h"

#include "general/memory.h"

struct ProcessInfo;

class MockMemory : public Memory {
public:
    MOCK_CONST_METHOD0(Info, const ProcessInfo&());
    MOCK_METHOD0(Total, long long());
};

#endif // MOCK_MEMORY_H
