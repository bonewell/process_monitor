#ifndef MOCK_MEMORY_LISTENER_H
#define MOCK_MEMORY_LISTENER_H

#include "gmock/gmock.h"

#include "memory_listener.h"

struct ProcessInfo;

class MockMemoryListener : public MemoryListener {
public:
    MOCK_METHOD2(OnMemoryChanged, void(const ProcessInfo& info, long long value));
};

#endif // MOCK_MEMORY_LISTENER_H
