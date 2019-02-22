#include <iostream>

#include "runner.h"

int main(int argc, char *argv[])
{
    if (argc < 3) {
       std::cout << "Use: process_monitor <process_name> [<process_name>...] <log_file>\n";
    }

    Runner::ProcessNames names;
    for (auto i = 1; i < argc; ++i) {
        names.push_back(argv[i]);
    }
    const auto logs = argv[argc-1];

    return Runner{names, logs}.Run();
}
