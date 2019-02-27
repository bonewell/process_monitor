#ifndef RUNNER_H
#define RUNNER_H

#include <list>
#include <string>
#include <vector>

#include "logger.h"
#include "process.h"

class Runner
{
public:
    using ProcessNames = std::vector<std::string>;

    Runner(ProcessNames names, std::string logs);
    int Start();
    void Stop();

private:
    using Processes = std::list<Process>;

    void Run();
    ProcessNames names_;
    Logger logger_;
    Processes processes_;
};

#endif // RUNNER_H
