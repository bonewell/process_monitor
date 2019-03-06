#include "process.h"

class TestableProcess : public Process {
public:
    using Process::Find;

    TestableProcess(std::string name, std::unique_ptr<Reader> reader) :
        Process(name, std::move(reader)) {}
};
