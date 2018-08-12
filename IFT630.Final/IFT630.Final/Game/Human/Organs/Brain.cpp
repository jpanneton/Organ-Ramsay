#include "Brain.h"
#include "Engine/Utilities/Math.h"
#include "Game/Human/Body.h"
#include "Game/Human/OrganIdentifiers.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <chrono>
#include <iostream>

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
				m_body.getInfo().energyLevel -= 0.005f;				
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
				m_body.getInfo().energyLevel -= 0.005f;
				
            }
            elapsedSeconds = 0.f;
        }

        elapsedSeconds += 1.f / fps;
        return organTriggered;
    }

	bool Brain::updateStomach(float fps)
	{
		bool organTriggered = false;

		if (m_body.getInfo().energyLevel < BodySettings::MIN_ENERGY_LEVEL)
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

		if (m_body.getInfo().excrementLevel > BodySettings::OPTIMAL_EXCREMENT_LEVEL)
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

	void Brain::updateHappiness()
	{
		const float energyLevelDelta = BodySettings::OPTIMAL_ENERGY_LEVEL - m_body.getInfo().energyLevel;
		const float excrementLevelDelta = m_body.getInfo().excrementLevel - BodySettings::OPTIMAL_EXCREMENT_LEVEL;
		float energyLevelRatio = 0.f;
		float excrementLevelRatio = 0.f;

		if (energyLevelDelta >= 0.f)
		{
			energyLevelRatio = energyLevelDelta / (BodySettings::OPTIMAL_ENERGY_LEVEL - BodySettings::MIN_ENERGY_LEVEL);
		}

		if (excrementLevelDelta >= 0.f)
		{
			excrementLevelRatio = excrementLevelDelta / (BodySettings::OPTIMAL_EXCREMENT_LEVEL - BodySettings::MIN_EXCREMENT_LEVEL);
		}

		m_body.getInfo().happinessLevel = (1.f - energyLevelRatio) * (1.f - excrementLevelRatio);
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

			updateHappiness();
            elapsedSeconds = 0.f;

            if (heartTriggered || lungsTriggered || stomachTriggered || intestineTriggered)
                m_sprite.setColor(sf::Color(255, 235, 215));
        }

        elapsedSeconds += 1.f / fps;
    }

    void Brain::run()
    {

    }
}