#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "mock_reader.h"
#include "testable_process.h"

using ::testing::Eq;
using ::testing::Return;
using ::testing::InvokeWithoutArgs;

class Proc {
public:
    bool HasNext() {
        return it != std::end(names);
    }
    std::string Next() {
        return *it++;
    }
private:
    std::vector<std::string> names{"1", "3", "5"};
    std::vector<std::string>::iterator it{std::begin(names)};
};

TEST(ProcessTest, Find)
{
    MockReader* mock_reader_ptr = new MockReader{};
    std::unique_ptr<Reader> reader{mock_reader_ptr};
    TestableProcess ps{"bash", std::move(reader)};

    Proc proc;
    EXPECT_CALL(*mock_reader_ptr, HasNext()).Times(4).WillRepeatedly(
                InvokeWithoutArgs(&proc, &Proc::HasNext));
    EXPECT_CALL(*mock_reader_ptr, Next()).WillRepeatedly(
                InvokeWithoutArgs(&proc, &Proc::Next));
    EXPECT_CALL(*mock_reader_ptr, Rewind());

    Process::Pids expected{1, 3, 5, 7, 11, 13, 17, 19, 23,
                           29, 31, 37, 41, 43, 47, 53, 59, 61};

    ASSERT_THAT(ps.Find(), Eq(expected));
}
