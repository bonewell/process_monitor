#ifndef MOCK_MEMORY_H
#define MOCK_MEMORY_H

#include "gmock/gmock.h"

#include "memory.h"

class MockMemory : public Memory {
public:
    MOCK_METHOD0(Total, long long());
};

#endif // MOCK_MEMORY_H
