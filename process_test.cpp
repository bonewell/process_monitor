#include "gtest/gtest.h"

#include "testable_process.h"
#include "dirreader.h"

TEST(ProcessTest, Find)
{
    TestableProcess p{"bash"};
    auto pids = p.Find();
    ASSERT_FALSE(pids.empty());
}
