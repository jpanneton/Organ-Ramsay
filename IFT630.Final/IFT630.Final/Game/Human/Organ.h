#pragma once

#include "Engine/ThreadSignaler.h"
#include <SFML/Graphics/Sprite.hpp>
#include <atomic>
#include <memory>
#include <thread>

namespace Human
{
    class Body;
    class Organ
    {
    public:
        using Ptr = std::unique_ptr<Organ>;

        Organ(Body& body);
        virtual ~Organ();
        virtual void update(float fps) = 0;
        virtual void draw() const;

        void start();
        void trigger();
        void shutdown();

    protected:
        virtual void run() = 0;
        Body& m_body;
        ThreadSignaler m_signaler;
        long long m_handicap;
        std::atomic_bool m_running;
        sf::Sprite m_sprite;

    private:
        std::thread m_thread;
    };
}