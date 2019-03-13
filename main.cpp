#include <iostream>

#include "loop.h"
#include "monitor/status_monitor.h"
#include "proc/proc_reader.h"
#include "utils/logger.h"
#include "utils/signals.h"

int main(int argc, char *argv[])
{
    if (argc < 2) {
        std::cout << "Use: process_monitor <process_name> [<process_name>...]\n";
        return 0;
    }

    Signals signals;
    LOGGER_INIT("log4cplus.ini");

    StatusMonitor::Names names;
    for (auto i = 1; i < argc; ++i) {
        names.emplace(argv[i]);
    }

    ProcReader ps;
    StatusMonitor monitor{ps, names};
    Loop loop{monitor};

    return signals.Wait();
}
