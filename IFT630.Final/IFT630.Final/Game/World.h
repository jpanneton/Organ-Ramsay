#pragma once

// Name: World.h
// Author: Jérémi Panneton
// Description: Main game world class

#include "Engine/ResourceHolder.h"
#include "Engine/States/State.h"
#include "Game/ResourceIdentifiers.h"
#include "Game/Human/Body.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/View.hpp>
#include <vector>

/// @brief World elements (renderer, resources, scene graph, logical data, etc.)
/// @author Jeremi Panneton
/// @ingroup game
class World : sf::NonCopyable
{
public:
	/// @brief Construct the world with a main render window
	/// @param[in] context Main application context (shared resources)
	explicit World(State::Context context);

	/// @brief Update all world elements
	/// @param[in] dt Elapsed time since last update
	void update(sf::Time dt);

	/// @brief Draw all world elements
	void draw() const;

	/// @brief Handle keyboard event
	/// @param[in] event Input event
	void handleEvent(const sf::Event& event);

	/// @brief Move world camera
	/// @param[in] delta Delta to move the camera from its current position
    void moveCamera(const sf::Vector2f& delta);

	/// @brief Zoom world camera
	/// @param[in] position Zoom position (reference pixel)
	/// @param[in] zoomAmount Zoom amount (ex: 1.0 = no zoom, 0.7 = 30% zoom in, 1.3 = 30% zoom out)
    void zoomCamera(const sf::Vector2i& position, float zoomAmount);

private:
	/// @brief Build the main scene of the game (level)
	void buildScene();

	//========================================

	/// @brief Main application context (shared resources)
    State::Context m_context;
	/// @brief Main view (what's visible)
	sf::View m_worldView;
    /// @brief Dimensions of the world
    sf::FloatRect m_worldBounds;
	/// @brief Keyboard input
	std::string m_keyboardInput;

    /// @brief Human body
    Human::Body m_humanBody;
};