#include <iostream>

#include "runner.h"

int main(int argc, char *argv[])
{
    if (argc < 3) {
        std::cout << "Use: process_monitor <process_name> [<process_name>...] <log_file>\n";
        return 0;
    }

    Runner::ProcessNames names;
    for (auto i = 1; i < argc - 1; ++i) {
        names.push_back(argv[i]);
    }
    const auto logs = argv[argc-1];

    Runner{names, logs}.Run();

    return 0;
}
