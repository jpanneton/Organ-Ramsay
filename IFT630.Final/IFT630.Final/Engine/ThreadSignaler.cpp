#include "ThreadSignaler.h"

void ThreadSignaler::notify()
{
    std::lock_guard<std::mutex> lock(m_mutex);
    m_ready = true;
    m_conditionVariable.notify_one();
}

void ThreadSignaler::wait()
{
    std::unique_lock<std::mutex> lock(m_mutex);
    m_conditionVariable.wait(lock, [&] { return m_ready; });
    m_ready = false;
}