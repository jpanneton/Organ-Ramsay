#pragma once

#include <Game/Human/Organ.h>

namespace Human
{
    class Stomach : public Organ
    {
    public:
        Stomach(Body& body);
        void update(float fps) override;
        void run() override;
    };
}