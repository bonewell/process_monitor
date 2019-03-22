#include "gmock/gmock-matchers.h"
#include "gtest/gtest.h"

#include <sys/stat.h>
#include <sys/types.h>

#include "proc_reader.h"

using namespace ::testing;

namespace proc {

std::vector<general::ProcessInfo> read(ProcReader& reader)
{
    std::vector<general::ProcessInfo> items;
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

}  // namespace proc
