#include "logger.h"

Logger::Logger(std::string file) : ofs_{file}
{
}

void Logger::Report(std::string message)
{
    std::lock_guard<std::mutex> lock{m_};
    messages_.push(std::move(message));
    cv_.notify_one();
}

void Logger::Stop()
{
    running = false;
}

void Logger::Run()
{
    while (running) {
        std::unique_lock<std::mutex> lock{m_};
        if (!messages_.empty()) {
            ofs_ << messages_.front() << "\n";
            messages_.pop();
        } else {
            cv_.wait(lock, [this] {
                return !(this->running && this->messages_.empty());
            });
        }
    }
}
