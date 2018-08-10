#pragma once

#include "Engine/Utilities/Math.h"
#include <atomic>
#include <functional>
#include <string>

template<typename T>
class AtomicNumber
{
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

    std::string toString() const
    {
        return std::to_string(get());
    }

private:
    std::atomic<T> m_value;
};

using AtomicFloat = AtomicNumber<float>;
using AtomicDouble = AtomicNumber<double>;