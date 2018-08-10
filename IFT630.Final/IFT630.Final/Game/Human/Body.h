#pragma once

#include "Engine/AtomicNumber.h"
#include "Engine/States/State.h"
#include "Game/Human/Organ.h"
#include "Game/Human/OrganIdentifiers.h"
#include <SFML/Graphics/Text.hpp>
#include <unordered_map>
#include <unordered_set>

// Forward declaration
namespace sf
{
    class Font;
    class RenderWindow;
}

namespace Human
{
    namespace BodySettings
    {
        const unsigned int AGE = 20;

        // Heart
        const float MIN_HEART_RATE = 40;
        const float MAX_HEART_RATE = 220 - AGE;
        const float OPTIMAL_HEART_RATE = MAX_HEART_RATE / 2;

        // Lungs
        const float MIN_RESPIRATORY_RATE = 10;
        const float MAX_RESPIRATORY_RATE = 50;
        const float OPTIMAL_RESPIRATORY_RATE = 15;

        const float MIN_OXYGEN_LEVEL = 0.9f;
        const float MAX_OXYGEN_LEVEL = 1.f;
        const float OPTIMAL_OXYGEN_LEVEL = 0.95f;

        // Body
        const float MIN_WATER_LEVEL = 0.45f;
        const float MAX_WATER_LEVEL = 0.65f;
        const float OPTIMAL_WATER_LEVEL = 0.55f;

        const float MIN_NUTRIENT_LEVEL = 0.05f;
        const float MAX_NUTRIENT_LEVEL = 1.f;
        const float OPTIMAL_NUTRIENT_LEVEL = 0.5f;
    };

    struct BodyInfo
    {
        // Brain
        AtomicFloat sleepLevel = 1.f;

        // Heart
        AtomicFloat beatPerMinute = BodySettings::OPTIMAL_HEART_RATE;

        // Lungs
        AtomicFloat breathPerMinute = BodySettings::OPTIMAL_RESPIRATORY_RATE;
        AtomicFloat oxygenLevel = BodySettings::MIN_OXYGEN_LEVEL;

        // Body
        AtomicFloat waterLevel = BodySettings::OPTIMAL_WATER_LEVEL;
        AtomicFloat nutrientLevel = BodySettings::OPTIMAL_NUTRIENT_LEVEL;
    };

    class Body
    {
    public:
        Body(State::Context context);

        void init();
        void update(float fps);
        void draw() const;

        Organ* getOrgan(OrganID id);
        void setOrganState(OrganID id, bool running);
        BodyInfo& getInfo();
        const State::Context& getContext() const;

    private:
        BodyInfo m_infos;
        std::unordered_map<OrganID, Organ::Ptr> m_organs;
        std::unordered_set<OrganID> m_suspendedOrgans;

        sf::Sprite m_sprite;
        sf::Text m_bpmHeartText;
        sf::Text m_bpmLungsText;
        sf::Text m_oxygenLevelText;
        sf::Text m_nutrientLevelText;

        State::Context m_context;
    };
}