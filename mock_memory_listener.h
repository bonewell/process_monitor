#ifndef MOCK_MEMORY_LISTENER_H
#define MOCK_MEMORY_LISTENER_H

#include "gmock/gmock.h"

#include "memory_listener.h"

class MockMemoryListener : public MemoryListener {
public:
    MOCK_METHOD2(OnMemoryChanged, void(int pid, long long));
};

#endif // MOCK_MEMORY_LISTENER_H
