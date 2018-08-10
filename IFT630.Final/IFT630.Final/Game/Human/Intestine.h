#pragma once

#include <Game/Human/Organ.h>

namespace Human
{
    class Intestine : public Organ
    {
    public:
        Intestine(Body& body);
        void update(float fps) override;
        void run() override;
    };
}