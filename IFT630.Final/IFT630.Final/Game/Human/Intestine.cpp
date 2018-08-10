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
    }

    void Intestine::run()
    {
        while (m_running)
        {
            m_signaler.wait();
        }
    }
}