#ifndef READER_H
#define READER_H

#include <string>

class Reader
{
public:
    virtual bool HasNext() = 0;
    virtual std::string Next() = 0;
    virtual void Rewind() = 0;
    virtual ~Reader() = default;
};

#endif // READER_H
