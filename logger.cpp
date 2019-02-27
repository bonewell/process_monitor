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
    running_ = false;
}

void Logger::Run()
{
    running_ = true;
    while (running_) {
        std::unique_lock<std::mutex> lock{m_};
        if (!messages_.empty()) {
            lock.unlock();
            ofs_ << messages_.front() << std::endl;
            lock.lock();
            messages_.pop();
        } else {
            cv_.wait(lock, [this] {
                return !(this->running_ && this->messages_.empty());
            });
        }
    }
}
