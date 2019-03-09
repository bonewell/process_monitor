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
    NiceMock<MockMemory> memory;
    MemoryMonitor monitor{memory, 5};
    ON_CALL(memory, Total()).WillByDefault(Return(1500000));

    MockMemoryListener listener;
    monitor.Subscribe(&listener);

    EXPECT_CALL(listener, OnMemoryChanged(5, 1500000));
    monitor.Measure();
}

TEST(MemoryMonitorTest, NotExcessLimit)
{
    NiceMock<MockMemory> memory;
    MemoryMonitor monitor{memory, 5};
    ON_CALL(memory, Total()).WillByDefault(Return(150000));

    MockMemoryListener listener;
    monitor.Subscribe(&listener);

    EXPECT_CALL(listener, OnMemoryChanged(_, _)).Times(0);
    monitor.Measure();
}
