#include "Heart.h"
#include "Game/Human/Body.h"
#include "Engine/Utilities/Math.h"
#include <iostream>

namespace Human
{
    Heart::Heart(Body& body)
        : Organ{ body }
    {
        m_sprite.setTexture(body.getContext().textures->get(TexturesID::HumanHeart));
        m_sprite.setOrigin(sf::Vector2f(m_sprite.getTexture()->getSize()) / 2.f);
        m_sprite.setPosition(420.f, 450.f);
    }

    void Heart::update(float fps)
    {
        static float x = -1.5f;
        // Normal dist : [-1.5, 1.5] peaking at ~1.0
        float normalValue = Util::normalDist(x, 0.f, 0.45f);
        sf::Uint8 color = static_cast<sf::Uint8>(175 + 75 * normalValue);
        m_sprite.setColor(sf::Color(color, 0, 0));
        m_sprite.setScale(1.f + 0.1f * normalValue, 1.f + 0.1f * normalValue);
        
        const float bps = m_body.getInfo().beatPerMinute / 60.f; // Beats per second
        const float xps = 3.f / fps; // x per second
        x += xps * bps;
        if (x > 1.5f)
        {
            x = -1.5f;
        }
    }

    void Heart::run()
    {
        while (m_running)
        {
            m_signaler.wait();
			if (!m_running)
				return;

            //std::cout << "Battement" << std::endl;
            //sleep(m_handicap);
        }
    }
}