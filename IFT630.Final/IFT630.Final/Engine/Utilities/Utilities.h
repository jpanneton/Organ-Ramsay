#pragma once

// Name: Utility.h
// Author: Jérémi Panneton
// Description: Game specific utility functions

#include <SFML/Graphics/Rect.hpp>

// Forward declaration
namespace sf
{
    class RenderWindow;
    class View;
}

namespace Util
{
	/// @brief Change origin of a transformable object from top left corner to center
	/// @param[out] obj Transformable object that implements getLocalBounds() method (like sf::Sprite or sf::Text)
	template<class TransformableType>
	void centerOrigin(TransformableType& obj)
	{
		sf::FloatRect bounds = obj.getLocalBounds();
		obj.setOrigin(std::floor(bounds.left + bounds.width / 2.f), std::floor(bounds.top + bounds.height / 2.f));
	}

    /// @brief Zoom view by preserving relative mouse position
    /// @param[in,out] window Render window
    /// @param[out] view View to transform
    /// @param[in] position Reference position (usually mouse position)
    /// @param[in] zoomAmount Zoom amount (ex: 1.0 = no zoom, 0.7 = 30% zoom in, 1.3 = 30% zoom out)
    void zoomViewAt(sf::RenderWindow& window, sf::View& view, const sf::Vector2i& position, float zoomAmount);

	/// @brief Sleep wrapper
	/// @param[in] duration Time to wait in milliseconds
	void sleep(long long duration);
}