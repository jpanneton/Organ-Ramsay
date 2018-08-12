#pragma once

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
	const float MAX_RESPIRATORY_RATE = 50;
	const float OPTIMAL_RESPIRATORY_RATE = 15;

	const float MIN_OXYGEN_LEVEL = 0.9f;
	const float MAX_OXYGEN_LEVEL = 1.f;
	const float OPTIMAL_OXYGEN_LEVEL = 0.95f;

	// Body
	const float MIN_WATER_LEVEL = 0.45f;
	const float MAX_WATER_LEVEL = 0.65f;
	const float OPTIMAL_WATER_LEVEL = 0.55f;

	const float MIN_NUTRIENT_LEVEL = 0.05f;
	const float MAX_NUTRIENT_LEVEL = 1.f;
	const float OPTIMAL_NUTRIENT_LEVEL = 0.5f;

	// Intestine
	const float MIN_SHIT_LEVEL = 0.f;
	const float MAX_SHIT_LEVEL = 1.f;
	const float OPTIMAL_SHIT_LEVEL = 0.75f;
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
	AtomicFloat oxygenLevel = BodySettings::MIN_OXYGEN_LEVEL;

	// Body
	AtomicFloat waterLevel = BodySettings::OPTIMAL_WATER_LEVEL;
	AtomicFloat nutrientLevel = BodySettings::OPTIMAL_NUTRIENT_LEVEL;
	AtomicFloat happinessLevel = 1.f;

	// Intestine
	AtomicFloat shitLevel = 0.5f;
};