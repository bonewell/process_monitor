#ifndef STATUS_MONITOR_H
#define STATUS_MONITOR_H

#include <string>
#include <unordered_set>

class ProcessTable;
class StatusListener;
enum class TypeEvent;

class StatusMonitor
{
public:
    using Listeners = std::unordered_set<StatusListener*>;
    using Names = std::unordered_set<std::string>;
    using Pids = std::unordered_set<int>;

    StatusMonitor(ProcessTable& table, Names names);
    void Subscribe(StatusListener* listener);
    void Unsubscribe(StatusListener* listener);
    void Scan();

private:
    inline Pids Collect() const;
    inline bool IsInteresting(const std::string& name) const;
    inline void NotifyAboutStarted(const Pids& pids) const;
    inline void NotifyAboutFinished(const Pids& pids) const;
    inline void Notify(int pid, TypeEvent event) const;
    ProcessTable& table_;
    Names names_;
    Listeners listeners_;
    Pids pids_;
};

#endif // STATUS_MONITOR_H
