#pragma once

// Name: Math.h
// Author: Jérémi Panneton (based on Patrice Roy work)
// Creation date: September 9th, 2015
// Description: Math utility functions

#include <limits>
#include <numeric>
#include <type_traits>

namespace Util
{
    template<class T = long double>
    static constexpr T Pi()
    {
        return static_cast<T>(3.1415926535897932384626433832795L);
    }

    template<class T>
    constexpr T Abs(T value)
    {
        return value < 0 ? -value : value;
    }

    template<class T>
    constexpr T Mod(T numerator, T denominator)
    {
        return denominator == 0 ?
            std::numeric_limits<T>::quiet_NaN() :
            numerator - static_cast<long long>(numerator / denominator) * denominator;
    }

    template<class T>
    constexpr T Pow(T base, unsigned int exponent)
    {
        return (exponent == 0) ? 1 : base * Pow(base, exponent - 1);
    }

    class Integral {};
    class Floating {};

    template<class T>
    constexpr bool AlmostEqual(T a, T b, T epsilon, Integral)
    {
        return a == b;
    }

    template<class T>
    constexpr bool AlmostEqual(T a, T b, T epsilon, Floating)
    {
        return Abs(a - b) < epsilon;
    }

    template<class T>
    constexpr bool AlmostEqual(T a, T b, T epsilon = std::numeric_limits<T>::epsilon())
    {
        return AlmostEqual(a, b, epsilon, std::conditional_t<std::is_integral<T>::value, Integral, Floating>{});
    }

    //========================================================

    constexpr unsigned long long Factorial(unsigned int n)
    {
        return n <= 1 ? 1 : (n * Factorial(n - 1));
    }

    namespace sqrt
    {
        template<class T>
        constexpr T SqrtLoop(T fg, T n, T lstX)
        {
            return (n == lstX) ? n : SqrtLoop(fg, (n + fg / n) / T{ 2.0 }, n);
        }
    }

    template<class T>
    constexpr T Sqrt(T value)
    {
        return sqrt::SqrtLoop(value, value / T{ 2.0 }, T{ 0.0 });
    }

    template<class T>
    constexpr T Hypot(T a, T b)
    {
        return Sqrt(Pow(a, 2) + Pow(b, 2));
    }

    inline float normalDist(float x, float mean = 0, float std = 1)
    {
        return ::exp(-0.5f * ::pow(x - mean, 2) / ::pow(std, 2)) / (std * ::sqrt(2.f * Pi<float>()));
    }
}