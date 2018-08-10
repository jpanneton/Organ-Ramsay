#pragma once

// Name: PauseState.h
// Author: Jérémi Panneton
// Description: Pause state class

#include "Engine/States/State.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

class PauseState : public State
{
public:
	/// @brief Construct a pause state
	/// @param[in] stack Owning stack
	/// @param[in] context Current game context
	PauseState(StateStack& stack, Context context);

	//----------------------------------------

	/// @see State::draw
	void draw() final;

	/// @see State::update
	bool update(sf::Time dt) final;

	/// @see State::handleEvent
	bool handleEvent(const sf::Event& event) final;

private:
	enum OptionNames
	{
		Play,
		Exit,
	};

	//========================================

	/// @brief Background image
	sf::Sprite m_backgroundSprite;
	/// @brief Game status
	sf::Text m_pausedText;
	/// @brief Instructions
	sf::Text m_instructionText;
};