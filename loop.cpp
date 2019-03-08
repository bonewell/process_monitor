#include "loop.h"

#include <thread>
#include <string.h>

#include "logger.h"
#include "status_monitor.h"
#include "process_table.h"

static LOGGER_INSTANCE("Process");

Loop::Loop(StatusMonitor& monitor)
    : monitor_{monitor}
{
}

void Loop::Start()
{
    thread_ = std::thread{&Loop::Run, this};
}

void Loop::Run()
{
    constexpr auto timeout = std::chrono::milliseconds(500);

    running_ = true;
    monitor_.Subscribe(this);
    while (running_) {
        monitor_.Scan();
        std::this_thread::sleep_for(timeout);
    }
    monitor_.Unsubscribe(this);
}

//{
//    std::vector<std::thread> process_threads;
//    for (const auto& name: names_) {
//        processes_.emplace_back(name);
//        process_threads.emplace_back(&Process::Monitor,
//                                     std::ref(processes_.back()));
//    }
//    for (auto& t: process_threads) {
//        t.join();
//    }
//}

void Loop::Stop()
{
    running_ = false;
    thread_.join();
}

void Loop::OnStarted(int pid)
{
    constexpr auto name = "<name>";
    LOGGER_INFO(name << " (" << pid << "): started");
}

void Loop::OnFinished(int pid)
{
    constexpr auto name = "<name>";
    LOGGER_INFO(name << " (" << pid << "): finished");
}
