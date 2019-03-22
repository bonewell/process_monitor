#ifndef MONITOR_MOCK_MEMORY_H
#define MONITOR_MOCK_MEMORY_H

#include "gmock/gmock.h"

#include "general/memory.h"

namespace general {

struct ProcessInfo;

class MockMemory : public Memory {
public:
    MOCK_CONST_METHOD0(Info, const ProcessInfo&());
    MOCK_METHOD0(Total, long long());
};

}  // namespace general

#endif  // MONITOR_MOCK_MEMORY_H
