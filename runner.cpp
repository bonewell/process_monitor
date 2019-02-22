#include "runner.h"

#include <iostream>
#include <thread>

#include <unistd.h>
#include <errno.h>
#include <string.h>

Runner::Runner(Runner::ProcessNames names, std::string logs)
    : names_{std::move(names)},
      logger_{std::move(logs)}
{
}

int Runner::Run()
{
    constexpr int nochdir{0};
    constexpr int noclose{0};

    auto res = daemon(nochdir, noclose);
    if (res != 0) {
        perror(strerror(errno));
        return res;
    } else {
        std::thread logger_thread{&Logger::Run, std::ref(logger_)};
        std::vector<std::thread> process_threads;
        for (const auto& name: names_) {
            processes_.emplace_back(name, logger_);
            process_threads.emplace_back(&Process::Monitor,
                                         std::ref(processes_.back()));
        }
        for (auto& t: process_threads) {
            t.join();
        }
        logger_thread.join();
    }

    return 0;
}

void Runner::Stop()
{
    for (auto& p: processes_) {
        p.Stop();
    }
    logger_.Stop();
}
