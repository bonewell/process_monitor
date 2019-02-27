#ifndef PROCESS_H
#define PROCESS_H

#include <atomic>
#include <string>
#include <set>

class Logger;

class Process
{
public:
    using Pids = std::set<int>;

    Process(std::string name, Logger& logger);
    void Monitor();
    void Stop();

private:
    bool IsMy(const std::string& pid) const;
    Pids Find() const;
    void Handle(Pids pids);
    void OnStarted(Pids pids);
    void OnFinished(Pids pids);

    std::string name_;
    Logger& logger_;
    std::atomic_bool running_{false};
    Pids pids_;
};

#endif // PROCESS_H
