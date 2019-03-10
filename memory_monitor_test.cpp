#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "memory_monitor.h"
#include "mock_memory.h"
#include "mock_memory_listener.h"

using ::testing::_;
using ::testing::NiceMock;
using ::testing::Return;

TEST(MemoryMonitorTest, ExcessLimit)
{
    auto* mock = new NiceMock<MockMemory>{};
    std::unique_ptr<Memory> memory{mock};
    MemoryMonitor monitor{std::move(memory), 5};
    ON_CALL(*mock, Total()).WillByDefault(Return(1500000));

    MockMemoryListener listener;
    monitor.Subscribe(&listener);

    EXPECT_CALL(listener, OnMemoryChanged(5, 1500000));
    monitor.Measure();
}

TEST(MemoryMonitorTest, NotExcessLimit)
{
    auto* mock = new NiceMock<MockMemory>{};
    std::unique_ptr<Memory> memory{mock};
    MemoryMonitor monitor{std::move(memory), 5};
    ON_CALL(*mock, Total()).WillByDefault(Return(150000));

    MockMemoryListener listener;
    monitor.Subscribe(&listener);

    EXPECT_CALL(listener, OnMemoryChanged(_, _)).Times(0);
    monitor.Measure();
}
