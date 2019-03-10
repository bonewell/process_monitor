#include "proc_memory.h"

#include <unistd.h>

namespace {
const std::string kProc = "/proc";
}  // namespace

ProcMemory::ProcMemory(int pid)
{
    const auto file = kProc + "/" + std::to_string(pid) + "/statm";
    ifs_.open(file);
}

ProcMemory::~ProcMemory()
{
    ifs_.close();
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
