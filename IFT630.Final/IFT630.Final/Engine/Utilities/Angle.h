#pragma once

// Name: Angle.h
// Author: Patrice Roy (adapted by Jérémi Panneton)
// URL: http://h-deb.clg.qc.ca/CLG/Cours/420KHJ/angle--options.html
// Creation date: September 9th, 2015
// Description: Angle class

#include "Engine/Utilities/Math.h"
#include <iostream>

class Degrees {};
class Radians {};

struct BaseAngleTraits
{
	using value_type = float; // Game specific
	static constexpr value_type Pi()
	{
		return static_cast<value_type>(3.14159);
	}
};

template<class>
struct AngleTraits;

template<class Source, class Destination>
constexpr BaseAngleTraits::value_type angle_cast(BaseAngleTraits::value_type);

//--------------------------------------------------------

template<>
struct AngleTraits<Degrees> : BaseAngleTraits
{
	static constexpr value_type DefaultValue()
	{
		return{};
	}

	static constexpr value_type MaxValue()
	{
		return value_type{ 360 };
	}

	static constexpr const char* Suffix()
	{
		return "deg";
	}

	static constexpr value_type ToRadians(value_type value)
	{
		return value / MaxValue() * value_type{ 2 } * Pi();
	}

	static constexpr value_type FromRadians(value_type value)
	{
		return value / (value_type{ 2 } * Pi()) * MaxValue();
	}

	static constexpr value_type Clamp(value_type value)
	{
		// e.g. -25 deg -> ((-25 % 360) + 360) % 360 = (-25 + 360) % 360 = 335 % 360 = 335 deg
		return static_cast<value_type>(Util::Mod(Util::Mod(value, MaxValue()) + MaxValue(), MaxValue()));
	}
};

//--------------------------------------------------------

template<>
struct AngleTraits<Radians> : BaseAngleTraits
{
	static constexpr value_type DefaultValue()
	{
		return{};
	}

	static constexpr value_type MaxValue()
	{
		return value_type{ 2 * Pi() };
	}

	static constexpr const char* Suffix()
	{
		return "rad";
	}

	static constexpr value_type ToRadians(value_type value)
	{
		return value;
	}

	static constexpr value_type FromRadians(value_type value)
	{
		return value;
	}

	static constexpr value_type Clamp(value_type value)
	{
		return static_cast<value_type>(Util::Mod(Util::Mod(value, MaxValue()) + MaxValue(), MaxValue()));
	}
};

//========================================================

template<class A>
class Angle
{
public:
	using value_type = typename AngleTraits<A>::value_type;
private:
	value_type value;
public:
	constexpr value_type Value() const
	{
		return value;
	}

	// Constructors

	constexpr Angle() : value{ AngleTraits<A>::DefaultValue() }
	{
	}

	constexpr Angle(value_type value) : value{ AngleTraits<A>::Clamp(value) }
	{
	}

	template<class T>
	constexpr Angle(const Angle<T>& angle) : value{ angle_cast<T, A>(angle.Value()) }
	{
	}

	// Relational operators

	constexpr bool operator==(const Angle& theta) const
	{
		return Util::Abs(Value() - theta.Value()) < 0.000001L;
	}

	constexpr bool operator!=(const Angle& theta) const
	{
		return !(*this == theta);
	}

	constexpr bool operator<(const Angle& theta) const
	{
		return Value() < theta.Value();
	}

	constexpr bool operator<=(const Angle& theta) const
	{
		return !(theta < *this);
	}

	constexpr bool operator>(const Angle& theta) const
	{
		return *this < theta;
	}

	constexpr bool operator>=(const Angle& theta) const
	{
		return !(*this < theta);
	}

	// Arithmetic operators (Angle & Angle)

	constexpr Angle operator+(const Angle& theta) const
	{
		return Angle<A>{ Value() + theta.Value() };
	}

	constexpr Angle operator-(const Angle& theta) const
	{
		return Angle<A>{ Value() - theta.Value() };
	}

	constexpr Angle operator*(const Angle& theta) const
	{
		return Angle<A>{ Value() * theta.Value() };
	}

	constexpr Angle operator/(const Angle& theta) const
	{
		return Angle<A>{ Value() / theta.Value() };
	}

	// Compound operators (Angle & Angle)
	
	Angle& operator+=(const Angle& theta)
	{
		return *this = *this + theta;
	}

	Angle& operator-=(const Angle& theta)
	{
		return *this = *this - theta;
	}

	Angle& operator*=(const Angle& theta)
	{
		return *this = *this * theta;
	}

	Angle& operator/=(const Angle& theta)
	{
		return *this = *this / theta;
	}

	// Arithmetic operators (Angle & Value)

	// +
	template<class T, typename = std::enable_if_t<std::is_fundamental<T>::value>>
	constexpr friend Angle operator+(const Angle& theta, T value)
	{
		return Angle<A>{ theta.Value() + value };
	}

	template<class T, typename = std::enable_if_t<std::is_fundamental<T>::value>>
	constexpr friend Angle operator+(T value, const Angle& theta)
	{
		return Angle<A>{ value + theta.Value() };
	}

	// -
	template<class T, typename = std::enable_if_t<std::is_fundamental<T>::value>>
	constexpr friend Angle operator-(const Angle& theta, T value)
	{
		return Angle<A>{ theta.Value() - value };
	}

	template<class T, typename = std::enable_if_t<std::is_fundamental<T>::value>>
	constexpr friend Angle operator-(T value, const Angle& theta)
	{
		return Angle<A>{ value - theta.Value() };
	}

	// *
	template<class T, typename = std::enable_if_t<std::is_fundamental<T>::value>>
	constexpr friend Angle operator*(const Angle& theta, T value)
	{
		return Angle<A>{ theta.Value() * value };
	}

	template<class T, typename = std::enable_if_t<std::is_fundamental<T>::value>>
	constexpr friend Angle operator*(T value, const Angle& theta)
	{
		return Angle<A>{ value * theta.Value() };
	}

	// /
	template<class T, typename = std::enable_if_t<std::is_fundamental<T>::value>>
	constexpr friend Angle operator/(const Angle& theta, T value)
	{
		return Angle<A>{ theta.Value() / value };
	}

	template<class T, typename = std::enable_if_t<std::is_fundamental<T>::value>>
	constexpr friend Angle operator/(T value, const Angle& theta)
	{
		return Angle<A>{ value / theta.Value() };
	}
};

//========================================================

template<class Source, class Destination>
constexpr BaseAngleTraits::value_type angle_cast(BaseAngleTraits::value_type value)
{
	return AngleTraits<Destination>::FromRadians(AngleTraits<Source>::ToRadians(value));
}

template<class A>
std::ostream& operator<<(std::ostream& os, const Angle<A>& theta)
{
	return os << theta.Value() << ' ' << AngleTraits<A>::Suffix();
}