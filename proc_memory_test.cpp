#include "gtest/gtest.h"
#include "gmock/gmock-matchers.h"

#include "proc_memory.h"

using ::testing::Eq;

TEST(ProcMemoryTest, Total)
{
    ProcessInfo info{getpid(), "bash"};
    ProcMemory m{info};
    auto v = m.Total();
    EXPECT_THAT(m.Total(), Eq(v));
}
