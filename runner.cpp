#include "runner.h"

#include <thread>

#include <unistd.h>
#include <errno.h>
#include <string.h>

Runner::Runner(Runner::ProcessNames names)
    : names_{std::move(names)}
{
}

void Runner::Run()
{
    std::vector<std::thread> process_threads;
    for (const auto& name: names_) {
        processes_.emplace_back(name);
        process_threads.emplace_back(&Process::Monitor,
                                     std::ref(processes_.back()));
    }
    for (auto& t: process_threads) {
        t.join();
    }
}

void Runner::Stop()
{
    for (auto& p: processes_) {
        p.Stop();
    }
}
