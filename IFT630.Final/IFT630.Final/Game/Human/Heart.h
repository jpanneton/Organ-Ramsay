#pragma once

#include <Game/Human/Organ.h>

namespace Human
{
    class Heart : public Organ
    {
    public:
        Heart(Body& body);
        void update(float fps) override;
        void run() override;

    private:
        float m_bpm;
    };
}