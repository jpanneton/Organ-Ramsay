#pragma once

#include "Engine/Utilities/Math.h"
#include "Engine/Utilities/Utilities.h"
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

    /*Number operator + (T value) { return Number(m_value + value); }
    Number operator - (T value) { return Number(m_value - value); }
    Number operator * (T value) { return Number(m_value * value); }
    Number operator / (T value) { return Number(m_value / value); }
    Number operator % (T value) { return Number(m_value % value); }*/

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


	void setProgressive(T step,T extremum, bool decreasing, long long stepDuration = 50)
	{
		std::lock_guard<std::mutex> lock(m_mutex);

		if (decreasing)
		{
			while (get() > extremum)
			{
				(*this) -= step;
				Util::sleep(stepDuration);
			}
		}
		else
		{
			while (get() < extremum)
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