#ifndef MOCK_STATUS_LISTENER_H
#define MOCK_STATUS_LISTENER_H

#include "gmock/gmock.h"
#include "status_listener.h"

class MockStatusListener : public StatusListener {
public:
    MOCK_METHOD1(OnStarted, void(int pid));
    MOCK_METHOD1(OnFinished, void(int pid));
};

#endif // MOCK_STATUS_LISTENER_H
