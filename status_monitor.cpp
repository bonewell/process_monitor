#include "status_monitor.h"

#include <algorithm>

#include "process_table.h"
#include "status_listener.h"

namespace {
inline bool IsNotPresented(const StatusMonitor::Pids& pids, int pid) {
    return pids.find(pid) == std::end(pids);
}
}

enum class TypeEvent { kStarted, kFinished };

StatusMonitor::StatusMonitor(ProcessTable& table, Names names)
    : table_{table},
      names_{names}
{
}

void StatusMonitor::Subscribe(StatusListener* listener)
{
    listeners_.insert(listener);
}

void StatusMonitor::Unsubscribe(StatusListener* listener)
{
    listeners_.erase(listener);
}

void StatusMonitor::Notify(int pid, TypeEvent event) const
{
    std::for_each(std::begin(listeners_), std::end(listeners_),
                  [pid, event](StatusListener* l) {
        switch (event) {
            case TypeEvent::kStarted: l->OnStarted(pid); break;
            case TypeEvent::kFinished: l->OnFinished(pid); break;
        }
    });
}

void StatusMonitor::Scan()
{
    auto pids = Collect();
    NotifyAboutStarted(pids);
    NotifyAboutFinished(pids);
    swap(pids_, pids);
}

std::unique_ptr<Memory> StatusMonitor::GetMemory(int pid)
{
    return table_.GetMemory(pid);
}

StatusMonitor::Pids StatusMonitor::Collect() const
{
    Pids pids;
    table_.Rewind();
    while (table_.HasNext()) {
        auto info = table_.Next();
        if (IsInteresting(info.name)) {
            pids.insert(info.pid);
        }
    }
    return pids;
}

void StatusMonitor::NotifyAboutStarted(const Pids& fresh_pids) const
{
    std::for_each(std::begin(fresh_pids), std::end(fresh_pids),
                  [this](int fresh_id) {
        if (IsNotPresented(pids_, fresh_id)) {
            Notify(fresh_id, TypeEvent::kStarted);
        }
    });
}

void StatusMonitor::NotifyAboutFinished(const Pids& fresh_pids) const
{
    std::for_each(std::begin(pids_), std::end(pids_),
                  [this, &fresh_pids](int id) {
        if (IsNotPresented(fresh_pids, id)) {
            Notify(id, TypeEvent::kFinished);
        }
    });
}

bool StatusMonitor::IsInteresting(const std::string& name) const
{
    return names_.find(name) != std::end(names_);
}
