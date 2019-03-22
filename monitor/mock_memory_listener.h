#ifndef MONITOR_MOCK_MEMORY_LISTENER_H
#define MONITOR_MOCK_MEMORY_LISTENER_H

#include "gmock/gmock.h"

#include "memory_listener.h"

namespace general {
struct ProcessInfo;
}  // namespace general

namespace monitor {

class MockMemoryListener : public MemoryListener {
public:
    MOCK_METHOD2(OnMemoryChanged, void(const general::ProcessInfo& info, long long value));
};

}  // namespace monitor

#endif  // MONITOR_MOCK_MEMORY_LISTENER_H
