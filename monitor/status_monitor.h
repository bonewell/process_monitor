#ifndef STATUS_MONITOR_H
#define STATUS_MONITOR_H

#include <memory>
#include <string>
#include <unordered_set>

#include "general/memory.h"
#include "general/process_table.h"

namespace monitor {
class StatusListener;
enum class TypeEvent;

class StatusMonitor
{
public:
    using Listeners = std::unordered_set<StatusListener*>;
    using Names = std::unordered_set<std::string>;
    using Infos = std::unordered_set<general::ProcessInfo,
                                     general::ProcessInfoHasher>;

    StatusMonitor(general::ProcessTable& table, Names names);
    void Subscribe(StatusListener* listener);
    void Unsubscribe(StatusListener* listener);
    void Scan();
    std::unique_ptr<general::Memory> GetMemory(const general::ProcessInfo& info);

private:
    inline Infos Collect() const;
    inline bool IsInteresting(const std::string& name) const;
    inline void NotifyAboutStarted(const Infos& fresh_infos) const;
    inline void NotifyAboutFinished(const Infos& fresh_infos) const;
    inline void Notify(const general::ProcessInfo& info, TypeEvent event) const;
    general::ProcessTable& table_;
    Names names_;
    Listeners listeners_;
    Infos infos_;
};

}  // namespace monitor

#endif // STATUS_MONITOR_H
