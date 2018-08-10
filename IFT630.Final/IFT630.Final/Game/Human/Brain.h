#pragma once

#include <Game/Human/Organ.h>

namespace Human
{
    class Brain : public Organ
    {
        class TimeManager
        {
        public:
            static const size_t FPS = 60;

            enum class TimeConstants : size_t
            {
                OneSecond = FPS,
                HalfSecond = FPS / 2,
                QuarterSecond = FPS / 4
            };

            void update()
            {
                ++m_frameCount;
            }

            bool isTime(TimeConstants time)
            {
                return m_frameCount % FPS == static_cast<size_t>(time);
            }

        private:
            size_t m_frameCount = 0;
        };

    public:
        Brain(Body& body);
        void update(float fps) override;
        void run() override;

    private:
        bool updateHeart(float fps);
        bool updateLungs(float fps);
	    bool updateStomach(float fps);
	    bool updateIntestine(float fps);
    };
}