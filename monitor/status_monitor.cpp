#include "status_monitor.h"

#include <algorithm>

#include "status_listener.h"

namespace {
inline bool IsNotPresented(const StatusMonitor::Infos& infos,
                           const ProcessInfo& info) {
    return infos.find(info) == std::end(infos);
}
}

enum class TypeEvent { kStarted, kFinished };

StatusMonitor::StatusMonitor(ProcessTable& table, Names names)
    : table_{table},
      names_{std::move(names)}
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
    auto fresh_infos = Collect();
    NotifyAboutStarted(fresh_infos);
    NotifyAboutFinished(fresh_infos);
    swap(infos_, fresh_infos);
}

std::unique_ptr<Memory> StatusMonitor::GetMemory(const ProcessInfo& info)
{
    return table_.GetMemory(info);
}

StatusMonitor::Infos StatusMonitor::Collect() const
{
    Infos infos;
    table_.Rewind();
    while (table_.HasNext()) {
        auto info = table_.Next();
        if (IsInteresting(info.name)) {
            infos.insert(info);
        }
    }
    return infos;
}

void StatusMonitor::NotifyAboutStarted(const Infos& fresh_infos) const
{
    std::for_each(std::begin(fresh_infos), std::end(fresh_infos),
                  [this](const ProcessInfo& fresh_info) {
        if (IsNotPresented(infos_, fresh_info)) {
            Notify(fresh_info, TypeEvent::kStarted);
        }
    });
}

void StatusMonitor::NotifyAboutFinished(const Infos& fresh_infos) const
{
    std::for_each(std::begin(infos_), std::end(infos_),
                  [this, &fresh_infos](const ProcessInfo& info) {
        if (IsNotPresented(fresh_infos, info)) {
            Notify(info, TypeEvent::kFinished);
        }
    });
}

bool StatusMonitor::IsInteresting(const std::string& name) const
{
    return names_.find(name) != std::end(names_);
}
