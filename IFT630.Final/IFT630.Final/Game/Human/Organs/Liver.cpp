#include "Liver.h"
#include "Game/Human/Body.h"

namespace Human
{
    Liver::Liver(Body& body)
        : Organ{ body }
    {
        m_sprite.setTexture(body.getContext().textures->get(TexturesID::HumanLiver));
        m_sprite.setColor(sf::Color(110, 45, 30));
    }

    void Liver::run()
    {
        while (m_running)
        {
            m_signaler.wait();
			if (!m_running)
				return;
        }
    }
}