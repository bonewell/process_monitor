#include "process.h"

#include <algorithm>
#include <iterator>
#include <regex>
#include <thread>

#include <dirent.h>
#include <sys/types.h>
#include <unistd.h>

#include "logger.h"

namespace {
const auto kProc = "/proc";
const auto kMemoryLimit = 1000000;  // bytes
const std::regex kPid{R"([0-9]+)"};

Process::Pids minus(const Process::Pids& a, const Process::Pids& b)
{
    Process::Pids diff;
    std::set_difference(std::begin(a), std::end(a),
                        std::begin(b), std::end(b),
                        std::inserter(diff, std::begin(diff)));
    return diff;
}
}

Process::Pids operator-(const Process::Pids& a, const Process::Pids& b)
{
    return minus(a, b);
}

Process::Process(std::string name, Logger &logger)
    : name_{std::move(name)},
      logger_{logger}
{
}

void Process::Stop()
{
    running_ = false;
}

bool Process::IsMy(const std::string& pid) const
{
    const auto file = std::string{kProc} + "/" + pid + "/comm";
    std::ifstream ifs{file};
    std::string bin;
    ifs >> bin;
    return bin == name_;
}

Process::Pids Process::Find() const
{
    Pids pids;
    auto* dirp = opendir(kProc);
    dirent* dp{nullptr};
    while ((dp = readdir(dirp)) != nullptr) {
        if (std::regex_match(dp->d_name, kPid) && IsMy(dp->d_name)) {
            pids.insert(std::stoi(dp->d_name));
        }
    }
    closedir(dirp);
    return pids;
}

void Process::Monitor()
{
    constexpr auto timeout = std::chrono::milliseconds(500);
    running_ = true;
    while (running_) {
        Handle(Find());
        std::this_thread::sleep_for(timeout);
    }
}

void Process::Handle(Pids pids)
{
    OnStarted(pids - pids_);
    OnFinished(pids_ - pids);
    mems_ = MemoryHandle(pids);
    pids_ = std::move(pids);
}

Process::Memory Process::MemoryHandle(const Pids& pids)
{
    Memory mems;
    for (auto p: pids) {
        auto old = mems_[p];
        auto memory = GetMemory(p);
        if (abs(memory - old) > kMemoryLimit) {
            OnMemoryChanged(p, memory);
        }
        mems[p] = memory;
    }
    return mems;
}

void Process::OnStarted(Pids pids)
{
    for (auto p: pids) {
        logger_.Report(name_ + " (" + std::to_string(p) + "): started");
    }
}

void Process::OnFinished(Pids pids)
{
    for (auto p: pids) {
        logger_.Report(name_ + " (" + std::to_string(p) + "): finished");
    }
}

void Process::OnMemoryChanged(int pid, long long value)
{
    logger_.Report(name_ + " (" + std::to_string(pid) + "): memory changed " + std::to_string(value));
}

long long Process::GetMemory(int pid) const
{
    const auto file = std::string{kProc} + "/" + std::to_string(pid) + "/statm";
    std::ifstream ifs{file};
    long long pages;
    ifs >> pages;
    return getpagesize() * pages;
}
