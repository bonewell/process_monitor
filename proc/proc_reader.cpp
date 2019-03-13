#include "proc_reader.h"

#include <fstream>
#include <regex>
#include <stdexcept>

#include <errno.h>
#include <string.h>
#include <sys/types.h>

#include "proc_memory.h"

namespace {
const std::string kProc = "/proc";
const std::regex kPid{R"([0-9]+)"};
}  // namespace

ProcReader::ProcReader()
{
    dirp_ = opendir(kProc.c_str());
    if (!dirp_) {
        auto error = errno;
        throw std::invalid_argument{strerror(error)};
    }
}

ProcReader::~ProcReader()
{
    closedir(dirp_);
}

bool ProcReader::HasNext()
{
    errno = 0;
    auto* dp = readdir(dirp_);
    auto error = errno;
    if (dp) {
        if (std::regex_match(dp->d_name, kPid)) {
            current_pid_ = dp->d_name;
            return true;
        }
        return HasNext();
    } else if (error == 0) {
        return false;
    } else {
        throw std::runtime_error{strerror(error)};
    }
}

ProcessInfo ProcReader::Next()
{
    auto name = GetName(current_pid_);
    return {std::stoi(current_pid_), name};
}

void ProcReader::Rewind()
{
    rewinddir(dirp_);
}

std::unique_ptr<Memory> ProcReader::GetMemory(const ProcessInfo& info)
{
    return std::unique_ptr<Memory>{new ProcMemory{info}};
}

std::string ProcReader::GetName(const std::string& pid) const
{
    const auto file = kProc + "/" + pid + "/comm";
    std::ifstream ifs{file};
    std::string bin;
    ifs >> bin;
    return bin;
}
