#ifndef STATUS_LISTENER_H
#define STATUS_LISTENER_H

class StatusListener {
public:
    virtual void OnStarted(int pid) = 0;
    virtual void OnFinished(int pid) = 0;
    virtual ~StatusListener() = default;
};

#endif // STATUS_LISTENER_H
