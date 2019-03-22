#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "general/process_info.h"
#include "memory_monitor.h"
#include "mock_memory.h"
#include "mock_memory_listener.h"

using ::testing::_;
using ::testing::NiceMock;
using ::testing::Return;
using ::testing::ReturnRef;

namespace monitor {

TEST(MemoryMonitorTest, ExcessLimit)
{
    auto* mock = new NiceMock<general::MockMemory>{};
    std::unique_ptr<general::Memory> memory{mock};
    MemoryMonitor monitor{std::move(memory)};
    ON_CALL(*mock, Total()).WillByDefault(Return(1500000));
    general::ProcessInfo info{5, "bash"};
    ON_CALL(*mock, Info()).WillByDefault(ReturnRef(info));

    MockMemoryListener listener;
    monitor.Subscribe(&listener);

    EXPECT_CALL(listener, OnMemoryChanged(info, 1500000));
    monitor.Measure();
}

TEST(MemoryMonitorTest, NotExcessLimit)
{
    auto* mock = new NiceMock<general::MockMemory>{};
    std::unique_ptr<general::Memory> memory{mock};
    MemoryMonitor monitor{std::move(memory)};
    ON_CALL(*mock, Total()).WillByDefault(Return(150000));

    MockMemoryListener listener;
    monitor.Subscribe(&listener);

    EXPECT_CALL(listener, OnMemoryChanged(_, _)).Times(0);
    monitor.Measure();
}

}  // namespace monitor
