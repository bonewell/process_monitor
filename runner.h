#ifndef RUNNER_H
#define RUNNER_H

#include <vector>
#include <string>

#include "logger.h"
#include "process.h"

class Runner
{
public:
    using ProcessNames = std::vector<std::string>;
    using Processes = std::vector<Process>;

    Runner(ProcessNames names, std::string logs);
    int Run();
    void Stop();

private:
    ProcessNames names_;
    Logger logger_;
    Processes processes_;
};

#endif // RUNNER_H
