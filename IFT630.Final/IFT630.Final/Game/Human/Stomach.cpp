#include "Stomach.h"
#include "Game/Human/Body.h"
#include <random>

namespace Human
{
    Stomach::Stomach(Body& body)
        : Organ{ body }
    {
        m_sprite.setTexture(body.getContext().textures->get(TexturesID::HumanStomach));
		m_sprite.setOrigin(sf::Vector2f(m_sprite.getTexture()->getSize()) / 2.f);
        m_sprite.setColor(sf::Color(250, 135, 120));
		m_sprite.setPosition(435.f, 559.f);
    }

	void Stomach::update(float fps)
	{
		m_sprite.setScale(1.f + 0.5f * m_body.getInfo().nutrientLevel, 1.f + 0.5f * m_body.getInfo().nutrientLevel);
	}

	void Stomach::run()
	{
		std::random_device rd;
		std::mt19937 gen(rd());

		while (m_running)
		{
			m_signaler.wait();
			if (!m_running)
				return;

			BodyInfo& infos = m_body.getInfo();
			std::uniform_real_distribution<float> dist(0.01f, 1.f - infos.nutrientLevel);
			float randomSnack = dist(gen);
			infos.nutrientLevel += randomSnack;
		}
	}
}
