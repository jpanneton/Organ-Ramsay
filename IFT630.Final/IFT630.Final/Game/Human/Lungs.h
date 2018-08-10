#pragma once

#include <Game/Human/Organ.h>

namespace Human
{
    class Lungs : public Organ
    {
        const float NUTRIENT_PER_ACTION = 0.05f;

    public:
        Lungs(Body& body);
        void update(float fps) override;
        void draw() const override;
        void run() override;

    private:
        sf::Sprite m_trachea;
    };
}