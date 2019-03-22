#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include <vector>

#include "mock_process_table.h"
#include "mock_status_listener.h"
#include "status_monitor.h"

using ::testing::_;
using ::testing::Invoke;
using ::testing::NiceMock;
using ::testing::Return;

namespace monitor {

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
    NiceMock<general::MockProcessTable> ps;
    StatusMonitor monitor{ps, {"bash"}};

    ReturnHasNext hasNext{true, false};
    ON_CALL(ps, HasNext()).WillByDefault(Invoke(std::ref(hasNext)));
    general::ProcessInfo info{5, "bash"};
    ON_CALL(ps, Next()).WillByDefault(Return(info));

    MockStatusListener listener;
    monitor.Subscribe(&listener);

    EXPECT_CALL(listener, OnStarted(info));
    monitor.Scan();
}

TEST(StatusMonitorTest, ProcessFinished)
{
    NiceMock<general::MockProcessTable> ps;
    StatusMonitor monitor{ps, {"bash"}};

    ReturnHasNext hasNext{true, false};
    ON_CALL(ps, HasNext()).WillByDefault(Invoke(std::ref(hasNext)));
    general::ProcessInfo info{5, "bash"};
    ON_CALL(ps, Next()).WillByDefault(Return(info));
    monitor.Scan();  // find process started

    MockStatusListener listener;
    monitor.Subscribe(&listener);

    EXPECT_CALL(listener, OnFinished(info));
    monitor.Scan();
}

TEST(StatusMonitorTest, ProcessAlreadyStarted)
{
    NiceMock<general::MockProcessTable> ps;
    StatusMonitor monitor{ps, {"bash"}};

    ReturnHasNext hasNext{true, false, true, false};
    ON_CALL(ps, HasNext()).WillByDefault(Invoke(std::ref(hasNext)));
    general::ProcessInfo info{5, "bash"};
    ON_CALL(ps, Next()).WillByDefault(Return(info));

    MockStatusListener listener;
    monitor.Subscribe(&listener);

    EXPECT_CALL(listener, OnStarted(info)).Times(1);
    monitor.Scan();
    monitor.Scan();
}

}  // namespace monitor
