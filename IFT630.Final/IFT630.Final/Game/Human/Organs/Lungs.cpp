#include "Lungs.h"
#include "Game/Human/Body.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <algorithm>
#include <iostream>

namespace Human
{
    Lungs::Lungs(Body& body)
        : Organ{ body }
    {
        m_sprite.setTexture(body.getContext().textures->get(TexturesID::HumanLungs));
        m_sprite.setOrigin(sf::Vector2f(m_sprite.getTexture()->getSize()) / 2.f);
        m_sprite.setPosition(410.f, 420.f);
        
        m_trachea.setTexture(body.getContext().textures->get(TexturesID::HumanLungsTrachea));
        m_trachea.setOrigin(sf::Vector2f(m_sprite.getTexture()->getSize()) / 2.f);
        m_trachea.setPosition(m_sprite.getPosition());
        m_trachea.setColor(sf::Color(175, 80, 70));
    }

    void Lungs::update(float fps)
    {
        static float x = -1.5f;
        // Normal dist : [-1.5, 1.5] peaking at ~1.0
        float normalValue = Util::normalDist(x, 0.f, 0.45f);
        sf::Uint8 color = static_cast<sf::Uint8>(175 + 75 * normalValue);
        m_sprite.setColor(sf::Color(color, 80, 70));
        m_sprite.setScale(0.95f + 0.05f * normalValue, 0.95f + 0.05f * normalValue);

        const float bps = m_body.getInfo().breathPerMinute / 60.f; // Breaths per second
        const float xps = 3.f / fps; // x per second
        x += xps * bps;
        if (x > 1.5f)
        {
            x = -1.5f;
        }
    }

    void Lungs::draw() const
    {
        m_body.getContext().window->draw(m_trachea);
        m_body.getContext().window->draw(m_sprite);
    }

    void Lungs::run()
    {
        while (m_running)
        {
            m_signaler.wait();
			if (!m_running)
				return;

            //std::cout << "Respiration" << std::endl;

            BodyInfo& infos = m_body.getInfo();
            if (infos.oxygenLevel < BodySettings::MAX_OXYGEN_LEVEL)
                infos.oxygenLevel += 0.005f;
            //printf("Oxygen level: %.6f", infos.oxygenLevel.get());
        }
    }
}