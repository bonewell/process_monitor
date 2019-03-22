#ifndef MONITOR_MOCK_STATUS_LISTENER_H
#define MONITOR_MOCK_STATUS_LISTENER_H

#include "gmock/gmock.h"

#include "status_listener.h"

namespace general {
struct ProcessInfo;
}  // namespace general

namespace monitor {

class MockStatusListener : public StatusListener {
public:
    MOCK_METHOD1(OnStarted, void(const general::ProcessInfo& info));
    MOCK_METHOD1(OnFinished, void(const general::ProcessInfo& info));
};

}  // namespace monitor

#endif  // MONITOR_MOCK_STATUS_LISTENER_H
