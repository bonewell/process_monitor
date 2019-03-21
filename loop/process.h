#ifndef LOOP_PROCESS_H
#define LOOP_PROCESS_H

#include <atomic>
#include <thread>

#include "general/process_info.h"

namespace loop {
class Loop;

class Process
{
public:
    Process(const general::ProcessInfo& info, Loop& loop);
    ~Process();

private:
    void Run();
    general::ProcessInfo info_;
    Loop& loop_;
    std::atomic_bool running_{false};
    std::thread thread_;
};

}  // namespace loop

#endif  // LOOP_PROCESS_H
