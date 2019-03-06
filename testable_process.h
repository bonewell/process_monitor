#include "process.h"

class TestableProcess : public Process {
public:
    using Process::Process;
    using Process::Find;
};
