#include "status_monitor.h"

#include <algorithm>

#include "process_table.h"
#include "status_listener.h"

namespace {
inline bool IsNotPresented(const StatusMonitor::Infos& pids,
                           const ProcessInfo& info) {
    return pids.find(info) == std::end(pids);
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

void StatusMonitor::Notify(const ProcessInfo& info, TypeEvent event) const
{
    std::for_each(std::begin(listeners_), std::end(listeners_),
                  [&info, event](StatusListener* l) {
        switch (event) {
            case TypeEvent::kStarted: l->OnStarted(info); break;
            case TypeEvent::kFinished: l->OnFinished(info); break;
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

StatusMonitor::Infos StatusMonitor::Collect() const
{
    Infos pids;
    table_.Rewind();
    while (table_.HasNext()) {
        auto info = table_.Next();
        if (IsInteresting(info.name)) {
            pids.insert(info);
        }
    }
    return pids;
}

void StatusMonitor::NotifyAboutStarted(const Infos& fresh_pids) const
{
    std::for_each(std::begin(fresh_pids), std::end(fresh_pids),
                  [this](const ProcessInfo& fresh_info) {
        if (IsNotPresented(pids_, fresh_info)) {
            Notify(fresh_info, TypeEvent::kStarted);
        }
    });
}

void StatusMonitor::NotifyAboutFinished(const Infos& fresh_pids) const
{
    std::for_each(std::begin(pids_), std::end(pids_),
                  [this, &fresh_pids](const ProcessInfo& info) {
        if (IsNotPresented(fresh_pids, info)) {
            Notify(info, TypeEvent::kFinished);
        }
    });
}

bool StatusMonitor::IsInteresting(const std::string& name) const
{
    return names_.find(name) != std::end(names_);
}
