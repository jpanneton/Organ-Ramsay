#include "Stomach.h"
#include "Game/Human/Body.h"
#include <random>

namespace Human
{
    Stomach::Stomach(Body& body)
        : Organ{ body }
    {
        m_sprite.setTexture(body.getContext().textures->get(TexturesID::HumanStomach));
        m_sprite.setColor(sf::Color(250, 135, 120));
		m_sprite.setPosition(371.f, 495.f);
    }

    void Stomach::update(float fps)
    {
    }

    void Stomach::run()
    {
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<float> dist(0.1f, 0.75f);
		
        while (m_running)
        {
            m_signaler.wait();
        }
    }
}