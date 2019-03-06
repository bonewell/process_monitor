#include "gtest/gtest.h"

#include "testable_process.h"

TEST(ProcessTest, Find)
{
  TestableProcess p{"bash"};
  auto pids = p.Find();
}
