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
		m_sprite.setScale(1.f + 0.5f * m_body.getInfo().energyLevel, 1.f + 0.5f * m_body.getInfo().energyLevel);
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
			std::uniform_real_distribution<float> distSnack(0.01f, 1.f - infos.energyLevel);
			float randomSnack = distSnack(gen);
			std::uniform_real_distribution<float> distExcrement(0.25f, 0.5f);
			float randomDigestion = distExcrement(gen);

			float temp = infos.energyLevel + randomSnack*(1 - randomDigestion);
			infos.energyLevel.setProgressive(0.005f, temp, false);

			temp = infos.excrementLevel + std::min(1 - infos.excrementLevel.get(), randomSnack*randomDigestion);
			infos.excrementLevel.setProgressive(0.005f, temp, false);			
		}
	}
}
