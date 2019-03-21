#ifndef UTILS_SIGNALS_H
#define UTILS_SIGNALS_H

#include <vector>

namespace utils {

class Signals final {
public:
    Signals();
    explicit Signals(std::initializer_list<int> signals);
    int Wait();

private:
    void Unsubscribe();
    std::vector<int> signals_;
};

}  // namespace utils

#endif  // UTILS_SIGNALS_H
