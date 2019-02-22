#ifndef PROCESS_H
#define PROCESS_H

#include <string>

class Logger;

class Process
{
public:
    Process(std::string name, Logger& logger);
    void Monitor();
    void Stop();

private:
    std::string name_;
    Logger& logger_;
};

#endif // PROCESS_H
