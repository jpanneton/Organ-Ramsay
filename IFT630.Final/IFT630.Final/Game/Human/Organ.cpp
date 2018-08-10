#include "Organ.h"
#include "Game/Human/Body.h"
#include <SFML/Graphics/RenderWindow.hpp>

namespace Human
{
    Organ::Organ(Body& body)
        : m_body{ body }
        , m_handicap{ 0 }
        , m_running{ false }
    {
    }

    Organ::~Organ()
    {
        shutdown();
    }

    void Organ::draw() const
    {
        m_body.getContext().window->draw(m_sprite);
    }

    void Organ::trigger()
    {
        m_signaler.notify();
    }

    void Organ::start()
    {
        m_running = true;
        m_thread = std::thread(&Organ::run, this);
    }

    void Organ::shutdown()
    {
        m_running = false;
        trigger();
        if (m_thread.joinable())
            m_thread.join();
    }
}