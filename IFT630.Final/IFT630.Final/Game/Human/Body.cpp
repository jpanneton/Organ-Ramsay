#include "Body.h"
#include "Game/ResourceIdentifiers.h"
#include "Game/Human/Organs/Brain.h"
#include "Game/Human/Organs/Heart.h"
#include "Game/Human/Organs/Intestine.h"
#include "Game/Human/Organs/Liver.h"
#include "Game/Human/Organs/Lungs.h"
#include "Game/Human/Organs/Stomach.h"
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

namespace Human
{
    Body::Body(State::Context context)
        : m_context{ context }
		, m_mouth{ *this }
    {
        m_organs.reserve(static_cast<size_t>(OrganID::COUNT));
        m_inactiveOrgans.reserve(static_cast<size_t>(OrganID::COUNT));
    }

    void Body::init()
    {
        m_context.textures->load(TexturesID::HumanBody, "Resources/Textures/Human/Body.png");
        m_context.textures->load(TexturesID::HumanBrain, "Resources/Textures/Human/Brain.png");
        m_context.textures->load(TexturesID::HumanHeart, "Resources/Textures/Human/Heart.png");
        m_context.textures->load(TexturesID::HumanLungs, "Resources/Textures/Human/LungsOnly.png");
        m_context.textures->load(TexturesID::HumanLungsTrachea, "Resources/Textures/Human/LungsTrachea.png");
        m_context.textures->load(TexturesID::HumanStomach, "Resources/Textures/Human/Stomach.png");
        m_context.textures->load(TexturesID::HumanLiver, "Resources/Textures/Human/Liver.png");
        m_context.textures->load(TexturesID::HumanIntestine, "Resources/Textures/Human/Intestine.png");

        m_sprite.setTexture(m_context.textures->get(TexturesID::HumanBody));
        m_organs[OrganID::Brain] = std::make_unique<Brain>(*this);
        m_organs[OrganID::Heart] = std::make_unique<Heart>(*this);
        m_organs[OrganID::Lungs] = std::make_unique<Lungs>(*this);
        m_organs[OrganID::Stomach] = std::make_unique<Stomach>(*this);
        m_organs[OrganID::Liver] = std::make_unique<Liver>(*this);
        m_organs[OrganID::Intestine] = std::make_unique<Intestine>(*this);

        for (const auto& organ : m_organs)
        {
            organ.second->start();
        }

        const sf::Font& font = m_context.fonts->get(FontsID::Main);

        m_bpmHeartText.setFont(font);
        m_bpmHeartText.setPosition(5.f, 15.f);

        m_bpmLungsText.setFont(font);
        m_bpmLungsText.setPosition(5.f, 45.f);

        m_oxygenLevelText.setFont(font);
        m_oxygenLevelText.setPosition(5.f, 75.f);

        m_energyLevelText.setFont(font);
        m_energyLevelText.setPosition(5.f, 105.f);

		m_excrementLevelText.setFont(font);
		m_excrementLevelText.setPosition(5.f, 135.f);

		m_happinessLevelText.setFont(font);
		m_happinessLevelText.setPosition(5.f, 165.f);
    }

    void Body::update(float fps)
    {
        static float elapsedSeconds = 0.f;

        m_organs.find(OrganID::Brain)->second->update(fps);
        m_organs.find(OrganID::Heart)->second->update(fps);
        m_organs.find(OrganID::Lungs)->second->update(fps);
        m_organs.find(OrganID::Stomach)->second->update(fps);
        m_organs.find(OrganID::Liver)->second->update(fps);
        m_organs.find(OrganID::Intestine)->second->update(fps);

        if (elapsedSeconds > 1.f) // 1 update / second
        {
            m_infos.oxygenLevel -= 0.002f;			
            elapsedSeconds = 0.f;
        }

		// Smile generation
		m_mouth.update(fps);

        m_bpmHeartText.setString("BPM (heart): " + std::to_string(static_cast<int>(m_infos.beatPerMinute.get())));
        m_bpmLungsText.setString("BPM (lungs): " + std::to_string(static_cast<int>(m_infos.breathPerMinute.get())));
        m_oxygenLevelText.setString("OXYGEN: " + m_infos.oxygenLevel.toString());
        m_energyLevelText.setString("ENERGY: " + m_infos.energyLevel.toString());
		m_excrementLevelText.setString("EXCREMENT: " + m_infos.excrementLevel.toString());
		m_happinessLevelText.setString("HAPPINESS: " + m_infos.happinessLevel.toString());

        elapsedSeconds += 1.f / fps;
    }

    void Body::draw() const
    {
        m_context.window->draw(m_sprite);
        m_organs.find(OrganID::Brain)->second->draw();
        m_organs.find(OrganID::Intestine)->second->draw();
        m_organs.find(OrganID::Stomach)->second->draw();
        m_organs.find(OrganID::Liver)->second->draw();
        m_organs.find(OrganID::Lungs)->second->draw();
        m_organs.find(OrganID::Heart)->second->draw();

		m_mouth.draw();
        
        m_context.window->setView(m_context.window->getDefaultView());
        m_context.window->draw(m_bpmHeartText);
        m_context.window->draw(m_bpmLungsText);
        m_context.window->draw(m_oxygenLevelText);
        m_context.window->draw(m_energyLevelText);
		m_context.window->draw(m_excrementLevelText);
		m_context.window->draw(m_happinessLevelText);
    }

    Organ* Body::getOrgan(OrganID id)
    {
        if (m_inactiveOrgans.find(id) != m_inactiveOrgans.end())
            return nullptr;

        auto organIt = m_organs.find(id);
        if (organIt == m_organs.end())
            return nullptr;
        return organIt->second.get();
    }

    void Body::setOrganState(OrganID id, bool running)
    {
        if (!running)
            m_inactiveOrgans.insert(id);
        else
            m_inactiveOrgans.erase(id);
    }

    BodyInfo& Body::getInfo()
    {
        return m_infos;
    }

	const BodyInfo& Body::getInfo() const
	{
		return m_infos;
	}

	bool Body::setInfo(std::string command)
	{
		// Remove spaces
		command.erase(std::remove_if(command.begin(), command.end(), ::isspace), command.end());
		// To lowercase
		std::transform(command.begin(), command.end(), command.begin(), ::tolower);

		size_t index = command.find('=');
		std::string parameter = command.substr(0, index);
		std::string valueStr = command.substr(index + 1);

		try
		{
			float value = std::stof(valueStr);

			if (parameter == "bpm")
				m_infos.beatPerMinute = CLAMP(HEART_RATE, value);
			else if (parameter == "cpm")
				m_infos.breathPerMinute = CLAMP(RESPIRATORY_RATE, value);
			else if (parameter == "oxygen")
				m_infos.oxygenLevel = CLAMP(OXYGEN_LEVEL, value);
			else if (parameter == "energy")
				m_infos.energyLevel = CLAMP(ENERGY_LEVEL, value);
			else if (parameter == "excrement")
				m_infos.excrementLevel = CLAMP(EXCREMENT_LEVEL, value);
			else if (parameter == "happiness")
				m_infos.happinessLevel = CLAMP(HAPPINESS_LEVEL, value);
			else
				return false;
		}
		catch (const std::invalid_argument&)
		{
			return false;
		}

		return true;
	}

    const State::Context& Body::getContext() const
    {
        return m_context;
    }
}