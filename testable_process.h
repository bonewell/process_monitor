#ifndef TESTABLE_PROCESS_H
#define TESTABLE_PROCESS_H

#include "process.h"

class TestableProcess : public Process {
public:
    using Process::Find;

    TestableProcess(std::string name, std::unique_ptr<ProcessTable> reader) :
        Process(name, std::move(reader)) {}
};

#endif  // TESTABLE_PROCESS_H
