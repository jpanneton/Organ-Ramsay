#pragma once

#include <condition_variable>
#include <mutex>

class ThreadSignaler
{
public:
    ThreadSignaler();
    void notify();
    void wait();

private:
    std::mutex m_mutex;
    std::condition_variable m_conditionVariable;
    bool m_ready = false;
};