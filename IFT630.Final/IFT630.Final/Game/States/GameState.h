#pragma once

// Name: GameState.h
// Author: Jérémi Panneton
// Description: Game state class

#include "Engine/States/State.h"
#include "Game/World.h"

/// @brief Game state (i.e. the game itself)
/// @author Jeremi Panneton
/// @ingroup game
class GameState : public State
{
public:
	/// @brief Construct a game state
	/// @param[in] stack Owning stack
	/// @param[in] context Current game context
	GameState(StateStack& stack, Context context);

	//----------------------------------------

	/// @see State::draw
	void draw() final;

	/// @see State::update
	bool update(sf::Time dt) final;

	/// @see State::handleEvent
	bool handleEvent(const sf::Event& event) final;

private:
	/// @brief Game's world
	World m_world;
};