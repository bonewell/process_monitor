#include "process.h"

#include <algorithm>
#include <iterator>
#include <regex>

#include <dirent.h>
#include <sys/types.h>

#include "logger.h"

namespace {
const auto kProc = "/proc";
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
    pids_ = std::move(pids);
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
