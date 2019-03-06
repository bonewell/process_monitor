#include "gtest/gtest.h"
#include "gmock/gmock-matchers.h"

#include <sys/stat.h>
#include <sys/types.h>

#include "dirreader.h"

using namespace ::testing;

std::vector<std::string> read(DirReader& reader)
{
    std::vector<std::string> items;
    while (reader.HasNext()) {
        items.push_back(reader.Next());
    }
    return items;
}

TEST(DirReaderTest, RewindProc)
{
    DirReader reader{"/proc"};
    auto before = read(reader);
    std::system("sleep 5 &");
    reader.Rewind();
    auto after = read(reader);
    ASSERT_THAT(before, Ne(after));
}
