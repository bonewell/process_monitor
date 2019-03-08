#include "gtest/gtest.h"
#include "gmock/gmock-matchers.h"

#include <sys/stat.h>
#include <sys/types.h>

#include "proc_reader.h"

using namespace ::testing;

bool operator==(const ProcessInfo& a, const ProcessInfo& b)
{
    return a.pid == b.pid;
}

std::vector<ProcessInfo> read(ProcReader& reader)
{
    std::vector<ProcessInfo> items;
    while (reader.HasNext()) {
        items.push_back(reader.Next());
    }
    return items;
}

TEST(ProcReaderTest, RewindProc)
{
    ProcReader reader{};
    auto before = read(reader);
    std::system("sleep 5 &");
    reader.Rewind();
    auto after = read(reader);
    ASSERT_THAT(before, Ne(after));
}
