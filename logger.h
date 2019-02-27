#ifndef LOGGER_H
#define LOGGER_H

#include <atomic>
#include <condition_variable>
#include <fstream>
#include <mutex>
#include <queue>
#include <string>

class Logger
{
public:
    explicit Logger(std::string file);
    void Report(std::string message);
    void Run();
    void Stop();

private:
    std::queue<std::string> messages_;
    std::ofstream ofs_;
    std::mutex m_;
    std::condition_variable cv_;
    std::atomic_bool running_{false};
};

#endif // LOGGER_H
