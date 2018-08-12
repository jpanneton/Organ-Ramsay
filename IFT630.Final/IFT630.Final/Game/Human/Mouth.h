#pragma once

#include <SFML/Graphics/VertexArray.hpp>

// Forward declaration
namespace sf
{
	class RenderWindow;
}

namespace Human
{
	class Body;

	class Mouth
	{
	public:
		Mouth(const Body& body);
		void update(float fps);
		void draw() const;

	private:
		const float length = 25.f;
		const float thickness = 5.f;

		const Body& m_body;
		sf::Vector2f m_position;
		sf::VertexArray m_points;
	};
}