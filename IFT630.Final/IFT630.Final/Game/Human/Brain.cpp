#include "Brain.h"
#include "Engine/Utilities/Math.h"
#include "Game/Human/Body.h"
#include "Game/Human/OrganIdentifiers.h"
#include <chrono>

namespace Human
{
    Brain::Brain(Body& body)
        : Organ{ body }
    {
        m_sprite.setTexture(body.getContext().textures->get(TexturesID::HumanBrain));
        m_sprite.setOrigin(sf::Vector2f(m_sprite.getTexture()->getSize()) / 2.f);
        m_sprite.setPosition(390.f, 140.f);
    }

    bool Brain::updateHeart(float fps)
    {
        static float elapsedSeconds = 0.f;
        const float secondsPerBeat = 60.f / m_body.getInfo().beatPerMinute;
        bool organTriggered = false;

        if (elapsedSeconds > secondsPerBeat)
        {
            Organ* heart = m_body.getOrgan(OrganID::Heart);
            if (heart)
            {
                heart->trigger();
                organTriggered = true;
				m_body.getInfo().nutrientLevel -= 0.005f;
				m_body.getInfo().shitLevel += 0.005f;
            }
            elapsedSeconds = 0.f;
        }

        elapsedSeconds += 1.f / fps;
        return organTriggered;
    }

    bool Brain::updateLungs(float fps)
    {
        static float elapsedSeconds = 0.f;
        bool organTriggered = false;
        
        const float oxygenLevelDelta = m_body.getInfo().oxygenLevel - BodySettings::OPTIMAL_OXYGEN_LEVEL;
        if (oxygenLevelDelta < 0.f)
        {
			m_body.getInfo().breathPerMinute += 0.05f;
        }
        else if (oxygenLevelDelta > 0.f && m_body.getInfo().breathPerMinute > BodySettings::OPTIMAL_RESPIRATORY_RATE)
        {
            m_body.getInfo().breathPerMinute -= 0.05f;
        }

        float secondsPerBreath = 60.f / m_body.getInfo().breathPerMinute;

        if (elapsedSeconds > secondsPerBreath)
        {
            Organ* lungs = m_body.getOrgan(OrganID::Lungs);
            if (lungs)
            {
                lungs->trigger();
                organTriggered = true;
				m_body.getInfo().nutrientLevel -= 0.005f;
				m_body.getInfo().shitLevel += 0.005f;
            }
            elapsedSeconds = 0.f;
        }

        elapsedSeconds += 1.f / fps;
        return organTriggered;
    }

	bool Brain::updateStomach(float fps)
	{

		bool organTriggered = false;

		const float nutrimentLevelDelta = m_body.getInfo().nutrientLevel - BodySettings::OPTIMAL_NUTRIENT_LEVEL;
		if (nutrimentLevelDelta < 0.f)
		{
			//A changer pour le hapiness;
		}
		else if (nutrimentLevelDelta > 0.f )
		{
			//a changer pour quelque chose quand trop plein;
		}

		if (m_body.getInfo().nutrientLevel < BodySettings::MIN_NUTRIENT_LEVEL)
		{
			Organ* stomach = m_body.getOrgan(OrganID::Stomach);
			if (stomach)
			{
				stomach->trigger();
				organTriggered = true;
			}			
		}
		
		return organTriggered;
	}

	bool Brain::updateIntestine(float fps)
	{

		bool organTriggered = false;

		const float shitLevelDelta = m_body.getInfo().shitLevel - BodySettings::OPTIMAL_SHIT_LEVEL;

		if (shitLevelDelta > BodySettings::OPTIMAL_SHIT_LEVEL)
		{
			//A changer pour le hapiness lvl
		}

		if (m_body.getInfo().shitLevel > BodySettings::OPTIMAL_SHIT_LEVEL)
		{
			Organ* intestine = m_body.getOrgan(OrganID::Intestine);
			if (intestine)
			{
				intestine->trigger();
				organTriggered = true;
			}
		}

		return organTriggered;
	}

    void Brain::update(float fps)
    {
        static float elapsedSeconds = 0.f;
        m_sprite.setColor(sf::Color(230, 195, 175));

        if (elapsedSeconds > 0.5f * (1.f - m_body.getInfo().sleepLevel)) // 2 updates / second
        {
            bool heartTriggered = updateHeart(fps);
            bool lungsTriggered = updateLungs(fps);
			bool stomachTriggered = updateStomach(fps);
			bool intestineTriggered = updateIntestine(fps);
            elapsedSeconds = 0.f;

            if (heartTriggered || lungsTriggered || stomachTriggered || intestineTriggered)
                m_sprite.setColor(sf::Color(255, 235, 215));
        }

        elapsedSeconds += 1.f / fps;
    }

    void Brain::run()
    {
        /*while (m_running)
        {
            Organ* heart = m_body.getOrgan(OrganID::Heart);
            if (heart)
            {
                heart->trigger();
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));

            Organ* lungs = m_body.getOrgan(OrganID::Lungs);
            if (lungs)
            {
                lungs->trigger();
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        }*/
    }
}