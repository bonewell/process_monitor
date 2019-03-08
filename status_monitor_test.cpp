#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "status_monitor.h"
#include "mock_process_table.h"
#include "mock_status_listener.h"

using ::testing::_;
using ::testing::Invoke;
using ::testing::NiceMock;
using ::testing::Return;

struct ProcessCounter {
    explicit ProcessCounter(int n) : count{n} {}
    bool operator() () {
        --count;
        return count >= 0;
    }
    int count;
};

TEST(StatusMonitorTest, ProcessStarted)
{
    NiceMock<MockProcessTable> ps;
    StatusMonitor monitor{ps, {"bash"}};

    ProcessCounter counter{1};
    ON_CALL(ps, HasNext()).WillByDefault(Invoke(std::ref(counter)));
    ON_CALL(ps, Next()).WillByDefault(Return(ProcessInfo{5, "bash"}));

    MockStatusListener listener;
    monitor.Subscribe(listener);

    EXPECT_CALL(listener, OnStarted(5));
    monitor.Scan();
}

TEST(StatusMonitorTest, ProcessFinished)
{
    NiceMock<MockProcessTable> ps;
    StatusMonitor monitor{ps, {"bash"}};

    ProcessCounter counter{1};
    ON_CALL(ps, HasNext()).WillByDefault(Invoke(std::ref(counter)));
    ON_CALL(ps, Next()).WillByDefault(Return(ProcessInfo{5, "bash"}));
    monitor.Scan();  // find process started

    MockStatusListener listener;
    monitor.Subscribe(listener);

    EXPECT_CALL(listener, OnFinished(5));
    monitor.Scan();
}
