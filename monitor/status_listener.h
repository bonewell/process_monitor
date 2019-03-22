#ifndef MONITOR_STATUS_LISTENER_H
#define MONITOR_STATUS_LISTENER_H

namespace general {
struct ProcessInfo;
}  // namespace general

namespace monitor {

class StatusListener {
public:
    virtual void OnStarted(const general::ProcessInfo& info) = 0;
    virtual void OnFinished(const general::ProcessInfo& info) = 0;
    virtual ~StatusListener() = default;
};

}  // namespace monitor

#endif  // MONITOR_STATUS_LISTENER_H
