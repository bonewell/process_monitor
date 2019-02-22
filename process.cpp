#include "process.h"

Process::Process(std::string name, Logger &logger)
    : name_{std::move(name)},
      logger_{logger}
{
}

void Process::Stop() {

}

void Process::Monitor()
{

}
