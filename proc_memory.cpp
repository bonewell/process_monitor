#include "proc_memory.h"

#include <unistd.h>

namespace {
const std::string kProc = "/proc/";
const auto kStatm = "/statm";
}  // namespace

ProcMemory::ProcMemory(ProcessInfo info)
    : info_{std::move(info)}
{
    const auto file = kProc + std::to_string(info_.pid) + kStatm;
    ifs_.open(file);
}

ProcMemory::~ProcMemory()
{
    ifs_.close();
}

const ProcessInfo &ProcMemory::Info() const
{
    return info_;
}

long long ProcMemory::Total()
{
    long long pages;
    ifs_ >> pages;
    if (!ifs_.bad()) {
        ifs_.seekg(0);
        return getpagesize() * pages;
    }
    return 0;
}
