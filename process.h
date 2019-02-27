#ifndef PROCESS_H
#define PROCESS_H

#include <atomic>
#include <string>
#include <set>
#include <unordered_map>

class Logger;

class Process
{
public:
    using Pids = std::set<int>;

    Process(std::string name, Logger& logger);
    void Monitor();
    void Stop();

private:
    using Memory = std::unordered_map<int, long long>;

    bool IsMy(const std::string& pid) const;
    long long GetMemory(int pid) const;
    Pids Find() const;
    void Handle(Pids pids);
    Memory MemoryHandle(const Pids& pids);
    void OnStarted(Pids pids);
    void OnFinished(Pids pids);
    void OnMemoryChanged(int pid, long long);

    std::string name_;
    Logger& logger_;
    std::atomic_bool running_{false};
    Pids pids_;
    Memory mems_;
};

#endif // PROCESS_H
