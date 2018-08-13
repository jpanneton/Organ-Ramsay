#pragma once

// Name: AtomicNumber.h
// Author: Jérémi Panneton
// Description: Atomic floating point number class

#include "Engine/Utilities.h"
#include <atomic>
#include <functional>
#include <mutex>
#include <string>

/// @brief Atomic floating point number wrapper
/// @tparam T Floating point type
/// @author Jeremi Panneton
/// @ingroup engine
template<typename T>
class AtomicNumber
{
	static_assert(std::is_floating_point<T>::value, "Type of AtomicNumber<T> must be a floating point type");

	/// @brief Perform arithmetic operation atomically
	/// @tparam[in] Operator Arithmetic operator type
	/// @param[in] value Value on which to apply the operator along with the current value
    template<template<typename U> class Operator>
    T performOperation(T value)
    {
        const Operator<T> op;
        auto current = get();
        // Equivalent to a single call to compare_exchange_strong
        while (!m_value.compare_exchange_weak(current, op(current, value)))
            ;
        return current;
    }

public:
    AtomicNumber(T value) : m_value(value) {}

    operator T() { return get(); }
    T get() const { return m_value.load(); }

    // Arithmetic operators
    void operator = (T value) { m_value = value; }

    // Number operator + (T value) { return Number(m_value + value); }
    // Number operator - (T value) { return Number(m_value - value); }
    // Number operator * (T value) { return Number(m_value * value); }
    // Number operator / (T value) { return Number(m_value / value); }
    // Number operator % (T value) { return Number(m_value % value); }

    T operator += (T value) { return performOperation<std::plus>(value); }
    T operator -= (T value) { return performOperation<std::minus>(value); }
    T operator *= (T value) { return performOperation<std::multiplies>(value); }
    T operator /= (T value) { return performOperation<std::divides>(value); }
    T operator %= (T value) { return performOperation<std::modulus>(value); }

    T operator ++ () { return performOperation<std::plus>(1); }
    T operator -- () { return performOperation<std::minus>(1); }
    T operator ++ (int) { return performOperation<std::plus>(1) - T(1); }
    T operator -- (int) { return performOperation<std::minus>(1) + T(1); }

    // Conditional operators
    bool operator == (T value) { return AlmostEqual(get(), value); }
    bool operator != (T value) { return get() != value; }
    bool operator > (T value) { return get() > value; }
    bool operator < (T value) { return get() < value; }
    bool operator >= (T value) { return get() >= value; }
    bool operator <= (T value) { return get() <= value; }

	/// @brief Set value by increasing / decreasing it progressively
	/// @param[in] value Value to reach
	/// @param[in] step Step by which to increase / decrease the value
	/// @param[in] stepDuration Time to wait between each step in milliseconds (speed)
	void setProgressive(T value, T step = 0.005, long long stepDuration = 50)
	{
		// Prevent two concurrent setProgressive calls from cancelling out each other (infinite loop)
		std::lock_guard<std::mutex> lock(m_mutex);

		if (get() > value)
		{
			while (get() > value)
			{
				(*this) -= step;
				Util::sleep(stepDuration);
			}
		}
		else
		{
			while (get() < value)
			{
				(*this) += step;
				Util::sleep(stepDuration);
			}
		}
	}

    std::string toString() const
    {
        return std::to_string(get());
    }

private:
    std::atomic<T> m_value;
	std::mutex m_mutex;
};

using AtomicFloat = AtomicNumber<float>;
using AtomicDouble = AtomicNumber<double>;