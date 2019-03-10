#ifndef PROCESS_INFO_H
#define PROCESS_INFO_H

#include <string>

struct ProcessInfo {
    int pid;
    std::string name;
};
bool operator==(const ProcessInfo& a, const ProcessInfo& b);

struct ProcessInfoHasher
{
  std::size_t operator()(const ProcessInfo& i) const;
};

#endif // PROCESS_INFO_H
