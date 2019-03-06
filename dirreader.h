#ifndef DIRREADER_H
#define DIRREADER_H

#include <dirent.h>

#include "reader.h"

class DirReader : public Reader
{
public:
    explicit DirReader(const std::string& name);
    ~DirReader() override;
    bool HasNext() override;
    std::string Next() override;
    void Rewind() override;

private:
    DIR* dirp_{nullptr};
    std::string current_;
};

#endif // DIRREADER_H
