#pragma once

#include <Game/Human/Organ.h>

namespace Human
{
    class Liver : public Organ
    {
    public:
        Liver(Body& body);
        void update(float fps) override;
        void run() override;
    };
}