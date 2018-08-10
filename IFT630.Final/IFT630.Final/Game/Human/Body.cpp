#include "Body.h"
#include "Game/ResourceIdentifiers.h"
#include "Game/Human/Brain.h"
#include "Game/Human/Heart.h"
#include "Game/Human/Intestine.h"
#include "Game/Human/Liver.h"
#include "Game/Human/Lungs.h"
#include "Game/Human/Stomach.h"
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

namespace Human
{
    Body::Body(State::Context context)
        : m_context{ context }
    {
        m_organs.reserve(static_cast<size_t>(OrganID::COUNT));
        m_suspendedOrgans.reserve(static_cast<size_t>(OrganID::COUNT));
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

        m_nutrientLevelText.setFont(font);
        m_nutrientLevelText.setPosition(5.f, 105.f);
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

        m_bpmHeartText.setString("BPM (heart): " + std::to_string(static_cast<int>(m_infos.beatPerMinute.get())));
        m_bpmLungsText.setString("BPM (lungs): " + std::to_string(static_cast<int>(m_infos.breathPerMinute.get())));
        m_oxygenLevelText.setString("OXYGEN: " + m_infos.oxygenLevel.toString());
        m_nutrientLevelText.setString("NUTRIENT: " + m_infos.nutrientLevel.toString());

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
        
        m_context.window->setView(m_context.window->getDefaultView());
        m_context.window->draw(m_bpmHeartText);
        m_context.window->draw(m_bpmLungsText);
        m_context.window->draw(m_oxygenLevelText);
        m_context.window->draw(m_nutrientLevelText);
    }

    Organ* Body::getOrgan(OrganID id)
    {
        if (m_suspendedOrgans.find(id) != m_suspendedOrgans.end())
            return nullptr;

        auto organIt = m_organs.find(id);
        if (organIt == m_organs.end())
            return nullptr;
        return organIt->second.get();
    }

    void Body::setOrganState(OrganID id, bool running)
    {
        if (!running)
            m_suspendedOrgans.insert(id);
        else
            m_suspendedOrgans.erase(id);
    }

    BodyInfo& Body::getInfo()
    {
        return m_infos;
    }

    const State::Context& Body::getContext() const
    {
        return m_context;
    }
}