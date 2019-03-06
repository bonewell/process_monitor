#ifndef MOCK_READER_H
#define MOCK_READER_H

#include "gmock/gmock.h"

#include "reader.h"

class MockReader : public Reader {
 public:
  MOCK_METHOD0(HasNext,
      bool());
  MOCK_METHOD0(Next,
      std::string());
  MOCK_METHOD0(Rewind,
      void());
};

#endif // MOCK_READER_H
