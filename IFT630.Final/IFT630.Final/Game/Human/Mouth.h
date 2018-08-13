#pragma once

// Name: Mouth.h
// Author: Jérémi Panneton
// Description: Mouth class

#include <SFML/Graphics/VertexArray.hpp>

// Forward declaration
namespace sf
{
	class RenderWindow;
}

namespace Human
{
	class Body;

	/// @brief Human mouth
	/// @author Jeremi Panneton
	/// @ingroup game
	class Mouth
	{
	public:
		/// @brief Construct a mouth (visual element)
		/// @param[in] body Body on which is attached the mouth
		Mouth(const Body& body);

		/// @see Organ::update
		void update(float fps);

		/// @see Organ::draw
		void draw() const;

	private:
		/// @see Mouth length in pixels
		const float LENGTH = 25.f;
		/// @see Mouth thickness in pixels
		const float THICKNESS = 5.f;

		/// Body on which is attached the mouth
		const Body& m_body;
		/// Position of the mouth in world coordinates
		sf::Vector2f m_position;
		/// Points of the mouth entity
		sf::VertexArray m_points;
	};
}