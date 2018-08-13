#include "Mouth.h"
#include "Engine/States/State.h"
#include "Game/Human/Body.h"
#include <SFML/Graphics/RenderWindow.hpp>

namespace Human
{
	Mouth::Mouth(const Body& body)
		: m_body{ body }
		, m_position{ 305.f, 239.f }
		, m_points{ sf::PrimitiveType::TriangleStrip }
	{
	}

	float quadratic(float x, float steepness)
	{
		return steepness * pow(x, 2);
	}

	float quadraticDerivative(float x, float steepness)
	{
		return steepness * x;
	}

	sf::Vector2f getUnitVector(float x, float y)
	{
		return sf::Vector2f(x, y) / (x * x + y * y);
	}

	void Mouth::update(float fps)
	{
		float happinessLevel = m_body.getInfo().happinessLevel.get();
		float steepness = 0.01f * (1.f - 2.f * happinessLevel);

		m_points.clear();
		for (float x = 0.f; x < LENGTH; x += 0.25f)
		{
			sf::Vector2f tangentVector(1.f, quadraticDerivative(x, 2.f * steepness));
			sf::Vector2f normalVector = getUnitVector(tangentVector.y, -tangentVector.x);

			sf::Vertex v1(m_position + sf::Vector2f(x, quadratic(x, steepness)));
			sf::Vertex v2 = v1.position + normalVector * THICKNESS;
			v1.color = sf::Color(100, 100, 100);
			v2.color = sf::Color::Black;

			if (x + 0.27f >= LENGTH)
			{
				sf::Vector2f normal = v2.position - v1.position;
				normal = getUnitVector(normal.y, -normal.x);
				v1.position += (v2.position - v1.position) / 2.f - normal * 15.f;
				v2.position = v1.position;
			}

			m_points.append(v1);
			m_points.append(v2);
		}
	}

	void Mouth::draw() const
	{
		m_body.getContext().window->draw(m_points);
	}
}