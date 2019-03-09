#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <vector>

#include "status_monitor.h"
#include "mock_process_table.h"
#include "mock_status_listener.h"

using ::testing::_;
using ::testing::Invoke;
using ::testing::NiceMock;
using ::testing::Return;

class ReturnHasNext {
public:
    explicit ReturnHasNext(std::initializer_list<bool> has_next)
        : has_next_{has_next}, it_{std::begin(has_next_)} {}
    bool operator() () { return *it_++; }
private:
    std::vector<bool> has_next_;
    std::vector<bool>::iterator it_;
};

TEST(StatusMonitorTest, ProcessStarted)
{
    NiceMock<MockProcessTable> ps;
    StatusMonitor monitor{ps, {"bash"}};

    ReturnHasNext hasNext{true, false};
    ON_CALL(ps, HasNext()).WillByDefault(Invoke(std::ref(hasNext)));
    ON_CALL(ps, Next()).WillByDefault(Return(ProcessInfo{5, "bash"}));

    MockStatusListener listener;
    monitor.Subscribe(&listener);

    EXPECT_CALL(listener, OnStarted(5));
    monitor.Scan();
}

TEST(StatusMonitorTest, ProcessFinished)
{
    NiceMock<MockProcessTable> ps;
    StatusMonitor monitor{ps, {"bash"}};

    ReturnHasNext hasNext{true, false};
    ON_CALL(ps, HasNext()).WillByDefault(Invoke(std::ref(hasNext)));
    ON_CALL(ps, Next()).WillByDefault(Return(ProcessInfo{5, "bash"}));
    monitor.Scan();  // find process started

    MockStatusListener listener;
    monitor.Subscribe(&listener);

    EXPECT_CALL(listener, OnFinished(5));
    monitor.Scan();
}

TEST(StatusMonitorTest, ProcessAlreadyStarted)
{
    NiceMock<MockProcessTable> ps;
    StatusMonitor monitor{ps, {"bash"}};

    ReturnHasNext hasNext{true, false, true, false};
    ON_CALL(ps, HasNext()).WillByDefault(Invoke(std::ref(hasNext)));
    ON_CALL(ps, Next()).WillByDefault(Return(ProcessInfo{5, "bash"}));

    MockStatusListener listener;
    monitor.Subscribe(&listener);

    EXPECT_CALL(listener, OnStarted(5)).Times(1);
    monitor.Scan();
    monitor.Scan();
}
