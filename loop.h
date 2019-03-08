#ifndef LOOP_H
#define LOOP_H

#include <atomic>
#include <thread>

#include "status_listener.h"

class StatusMonitor;

class Loop : public StatusListener
{
public:
    explicit Loop(StatusMonitor& monitor);
    void Start();
    void Stop();
    void OnStarted(int pid) override;
    void OnFinished(int pid) override;

private:
    void Run();
    StatusMonitor& monitor_;
    std::atomic_bool running_{false};
    std::thread thread_;
};

#endif // LOOP_H
