#ifndef RUNNER_H
#define RUNNER_H

#include <list>
#include <string>
#include <vector>

#include "process.h"

class Runner
{
public:
    using ProcessNames = std::vector<std::string>;

    explicit Runner(ProcessNames names);
    void Run();
    void Stop();

private:
    using Processes = std::list<Process>;

    ProcessNames names_;
    Processes processes_;
};

#endif // RUNNER_H
