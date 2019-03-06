#include "dirreader.h"

#include <stdexcept>

#include <errno.h>
#include <string.h>
#include <sys/types.h>

DirReader::DirReader(const std::string& name)
{
    dirp_ = opendir(name.c_str());
    if (!dirp_) {
        auto error = errno;
        throw std::invalid_argument{strerror(error)};
    }
}

DirReader::~DirReader()
{
    closedir(dirp_);
}

bool DirReader::HasNext()
{
    errno = 0;
    auto* dp = readdir(dirp_);
    auto error = errno;
    if (dp) {
        current_ = dp->d_name;
        return true;
    } else if (error == 0) {
        return false;
    } else {
        throw std::runtime_error{strerror(error)};
    }
}

std::string DirReader::Next()
{
    return std::move(current_);
}

void DirReader::Rewind()
{
    rewinddir(dirp_);
}
