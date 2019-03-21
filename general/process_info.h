#ifndef GENERAL_PROCESS_INFO_H
#define GENERAL_PROCESS_INFO_H

#include <string>

namespace general {

struct ProcessInfo {
    int pid;
    std::string name;
};
bool operator==(const ProcessInfo& a, const ProcessInfo& b);

struct ProcessInfoHasher
{
  std::size_t operator()(const ProcessInfo& i) const;
};

}  // namespace general

#endif  // GENERAL_PROCESS_INFO_H
