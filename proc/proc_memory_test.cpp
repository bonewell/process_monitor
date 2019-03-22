#include "gmock/gmock-matchers.h"
#include "gtest/gtest.h"

#include "proc_memory.h"

using ::testing::Eq;

namespace proc {

TEST(ProcMemoryTest, Total)
{
    general::ProcessInfo info{getpid(), "bash"};
    ProcMemory m{info};
    auto v = m.Total();
    EXPECT_THAT(m.Total(), Eq(v));
}

}  // namespace general
