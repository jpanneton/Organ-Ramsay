#pragma once

// Name: Application.h
// Author: Jérémi Panneton
// Description: Main game class

#include "Engine/States/StateStack.h"
#include "Game/World.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>

/// @brief Program's entry point (controls input, logic updates, rendering)
/// @author Jeremi Panneton
/// @ingroup engine
class Application : sf::NonCopyable
{
public:
	/// @brief Default constructor
	Application();

	/// @brief Game loop
	void run();

private:
	/// @brief Process all keyboard and mouse inputs
	void processInput();

	/// @brief Update all game elements
	/// @param[in] dt Elapsed time since last update
	void update(sf::Time dt);

	/// @brief Render all game elements on screen
	void render();

	//----------------------------------------

	/// @brief Update on-screen informations (i.e. fps)
	/// @param[in] dt Elapsed time since last update
	void updateStatistics(sf::Time dt);

	/// @brief Register application states
	void registerStates();

	//========================================

	/// @brief Time step between each update (fixed)
	static const sf::Time TimePerFrame;

	/// @brief Main render window (reference)
	sf::RenderWindow m_window;
	/// @brief Shared texture resources
	TextureHolder m_textures;
	/// @brief Shared font resources
	FontHolder m_fonts;

	/// @brief Application states
	StateStack m_stateStack;
	/// @brief Flag that stores if the game's window has the focus or not
	bool m_updateGame;

	sf::Text m_statisticsText;
	sf::Time m_statisticsUpdateTime;
	size_t m_statisticsNumFrames;
};