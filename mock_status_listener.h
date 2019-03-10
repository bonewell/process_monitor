#ifndef MOCK_STATUS_LISTENER_H
#define MOCK_STATUS_LISTENER_H

#include "gmock/gmock.h"

#include "status_listener.h"

struct ProcessInfo;

class MockStatusListener : public StatusListener {
public:
    MOCK_METHOD1(OnStarted, void(const ProcessInfo& info));
    MOCK_METHOD1(OnFinished, void(const ProcessInfo& info));
};

#endif // MOCK_STATUS_LISTENER_H
