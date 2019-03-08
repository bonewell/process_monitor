#include "status_monitor.h"

#include <algorithm>

#include "process_table.h"
#include "status_listener.h"

enum class TypeEvent { kStarted, kFinished };

StatusMonitor::StatusMonitor(ProcessTable& table, Names names)
    : table_{table},
      names_{names}
{
}

void StatusMonitor::Subscribe(StatusListener& listener)
{
    listeners_.push_back(&listener);
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
    Pids pids;
    table_.Rewind();
    while (table_.HasNext()) {
        auto info = table_.Next();
        if (IsFollowed(info.name)) {
            pids.insert(info.pid);
            Notify(info.pid, TypeEvent::kStarted);
        }
        pids_.erase(info.pid);
    }
    NotifyAboutFinished();
    swap(pids_, pids);
}

void StatusMonitor::NotifyAboutFinished() const
{
    std::for_each(std::begin(pids_), std::end(pids_),
                  [this](int pid) {
        Notify(pid, TypeEvent::kFinished);
    });
}

bool StatusMonitor::IsFollowed(const std::string& name) const
{
    return names_.find(name) != std::end(names_);
}
