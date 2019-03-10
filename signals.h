#ifndef SIGNALS_H
#define SIGNALS_H

#include <vector>

class Signals final {
public:
    Signals();
    explicit Signals(std::initializer_list<int> signals);
    int Wait();

private:
    void Unsubscribe();
    std::vector<int> signals_;
};

#endif  // SIGNALS_H
