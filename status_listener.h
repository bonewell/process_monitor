#ifndef STATUS_LISTENER_H
#define STATUS_LISTENER_H

struct ProcessInfo;

class StatusListener {
public:
    virtual void OnStarted(const ProcessInfo& info) = 0;
    virtual void OnFinished(const ProcessInfo& info) = 0;
    virtual ~StatusListener() = default;
};

#endif // STATUS_LISTENER_H
