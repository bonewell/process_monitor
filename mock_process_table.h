#ifndef MOCK_PROCESS_TABLE_H
#define MOCK_PROCESS_TABLE_H

#include "gmock/gmock.h"

#include "process_table.h"

class MockProcessTable : public ProcessTable {
 public:
  MOCK_METHOD0(HasNext,
      bool());
  MOCK_METHOD0(Next,
      ProcessInfo());
  MOCK_METHOD0(Rewind,
      void());
};

#endif // MOCK_PROCESS_TABLE_H
