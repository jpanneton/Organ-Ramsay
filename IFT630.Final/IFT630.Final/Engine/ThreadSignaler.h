#pragma once

// Name: ThreadSignaler.h
// Author: Jérémi Panneton
// Description: Thread signaling class

#include <condition_variable>
#include <mutex>

/// @brief Signaler that allows communication between different organs
/// @author Jeremi Panneton
/// @ingroup engine
class ThreadSignaler
{
public:
	/// @brief Default constructor
    ThreadSignaler() = default;

	/// @brief Notify waiting thread to execute
    void notify();

	/// @brief Put thread to sleep while waiting for a signal
    void wait();

private:
	/// @brief Mutex to allow safe usage of the condition variable
    std::mutex m_mutex;
	/// @brief Condition variable to wait and notify (monitor equivalent)
    std::condition_variable m_conditionVariable;
	/// @brief If a notification has been sent from the current instance
	/// @note Prevent spurious wakeups
    bool m_ready = false;
};