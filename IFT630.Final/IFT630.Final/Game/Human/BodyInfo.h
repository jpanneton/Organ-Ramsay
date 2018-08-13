#pragma once

// Name: BodyInfo.h
// Author: Jérémi Panneton
// Description: Body settings and informations

#include "Engine/AtomicNumber.h"

/// @brief Human body constraints
/// @author Jeremi Panneton
/// @ingroup game
namespace BodySettings
{
	const unsigned int AGE = 20;

	// Heart
	const float MIN_HEART_RATE = 40;
	const float MAX_HEART_RATE = 220 - AGE;
	const float OPTIMAL_HEART_RATE = MAX_HEART_RATE / 2;

	// Lungs
	const float MIN_RESPIRATORY_RATE = 10;
	const float MAX_RESPIRATORY_RATE = 65;
	const float OPTIMAL_RESPIRATORY_RATE = 15;

	const float MIN_OXYGEN_LEVEL = 0.9f;
	const float MAX_OXYGEN_LEVEL = 1.f;
	const float OPTIMAL_OXYGEN_LEVEL = 0.95f;

	// Body
	const float MIN_ENERGY_LEVEL = 0.05f;
	const float MAX_ENERGY_LEVEL = 1.f;
	const float OPTIMAL_ENERGY_LEVEL = 0.5f;

	const float MIN_HAPPINESS_LEVEL = 0.05f;
	const float MAX_HAPPINESS_LEVEL = 1.f;

	// Intestine
	const float MIN_EXCREMENT_LEVEL = 0.001f;
	const float MAX_EXCREMENT_LEVEL = 1.f;
	const float OPTIMAL_EXCREMENT_LEVEL = 0.5f;
};

/// @brief Human body parameters and statistics
/// @author Jeremi Panneton
/// @ingroup game
struct BodyInfo
{
	// Brain
	AtomicFloat sleepLevel = 1.f;

	// Heart
	AtomicFloat beatPerMinute = BodySettings::OPTIMAL_HEART_RATE;

	// Lungs
	AtomicFloat breathPerMinute = BodySettings::OPTIMAL_RESPIRATORY_RATE;
	AtomicFloat oxygenLevel = BodySettings::OPTIMAL_OXYGEN_LEVEL;

	// Body
	AtomicFloat energyLevel = BodySettings::OPTIMAL_ENERGY_LEVEL;
	AtomicFloat happinessLevel = BodySettings::MAX_HAPPINESS_LEVEL;

	// Intestine
	AtomicFloat excrementLevel = BodySettings::MIN_EXCREMENT_LEVEL;
};

#define CLAMP(param, value) std::max(std::min(value, BodySettings::MAX_##param), BodySettings::MIN_##param)