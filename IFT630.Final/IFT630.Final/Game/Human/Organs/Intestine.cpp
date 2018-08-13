#include "Intestine.h"
#include "Game/Human/Body.h"

namespace Human
{
    Intestine::Intestine(Body& body)
        : Organ{ body }
    {
        m_sprite.setTexture(body.getContext().textures->get(TexturesID::HumanIntestine));
        m_sprite.setColor(sf::Color(200, 150, 150));
    }

	void Intestine::update(float fps)
	{
		sf::Uint8 colorOffset = static_cast<sf::Uint8>(100 * m_body.getInfo().excrementLevel);
		m_sprite.setColor(sf::Color(200 - colorOffset, 150 - colorOffset, 150 - colorOffset));
	}

	void Intestine::run()
	{
		while (m_running)
		{
			m_signaler.wait();
			if (!m_running)
				return;

			BodyInfo& infos = m_body.getInfo();
			Util::sleep(5000);
			infos.excrementLevel.setProgressive(0.0051f);
		}
	}
}
