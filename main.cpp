#include <iostream>

#include "logger.h"
#include "runner.h"

int main(int argc, char *argv[])
{
    if (argc < 2) {
        std::cout << "Use: process_monitor <process_name> [<process_name>...]\n";
        return 0;
    }

    LOGGER_INIT("log4cplus.ini");

    Runner::ProcessNames names;
    for (auto i = 1; i < argc; ++i) {
        names.push_back(argv[i]);
    }

    Runner{names}.Run();

    return 0;
}
