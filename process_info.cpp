#include "process_info.h"

bool operator==(const ProcessInfo& a, const ProcessInfo& b)
{
    return a.pid == b.pid;
}

std::size_t ProcessInfoHasher::operator()(const ProcessInfo& i) const
{
    return std::hash<int>()(i.pid);
}
