#include "Intestine.h"
#include "Game/Human/Body.h"
#include <iostream>

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
		sf::Uint8 colorOffset = static_cast<sf::Uint8>(100 * m_body.getInfo().shitLevel);
		m_sprite.setColor(sf::Color(200 - colorOffset, 150 - colorOffset, 150 - colorOffset));
	}

	void Intestine::run()
	{
		m_signaler.wait();
		BodyInfo& infos = m_body.getInfo();
		std::cout << "c'est l'heure du caca" << std::endl;
		while(infos.shitLevel>0.0051f)
		{
			infos.shitLevel -= 0.005f;
			std::this_thread::sleep_for(std::chrono::milliseconds(50));
		}
		infos.shitLevel = 0;
		
	}
}
