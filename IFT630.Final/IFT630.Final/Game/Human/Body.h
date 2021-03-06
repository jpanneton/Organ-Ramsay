#pragma once

// Name: Body.h
// Author: J�r�mi Panneton
// Description: Body class

#include "Engine/States/State.h"
#include "Game/Human/BodyInfo.h"
#include "Game/Human/Mouth.h"
#include "Game/Human/OrganIdentifiers.h"
#include "Game/Human/Organs/Organ.h"
#include <SFML/Graphics/Text.hpp>
#include <unordered_map>

// Forward declarations
namespace sf
{
    class Font;
    class RenderWindow;
}

namespace Human
{
	/// @brief Human body
	/// @author Jeremi Panneton
	/// @ingroup game
    class Body
    {
    public:
		/// @brief Construct a base body (without organs)
		/// @param[in] context Main application context (shared resources)
        Body(State::Context context);

		/// @brief Load resources, start organs and create HUD
        void init();

		/// @brief Update all world elements
		/// @param[in] fps Frame rate
        void update(float fps);

		/// @brief Draw body
        void draw() const;

		/// @brief Get organ if it exists
		/// @param[in] id Organ ID
		/// @return Pointer to the organ instance
        Organ* getOrgan(OrganID id);

		/// @brief Get body statistics
		/// @return Body statistics
        BodyInfo& getInfo();

		/// @brief Get body statistics (readonly)
		/// @return Body statistics (readonly)
		const BodyInfo& getInfo() const;

		/// @brief Set body parameter from command
		/// @param[in] command User command
		/// @return If the command was valid or not
		bool setInfo(std::string command);

		/// @brief Get main application context
		/// @return Context containing all the shared resources
        const State::Context& getContext() const;

    private:
		/// @brief Main application context (shared resources)
		State::Context m_context;

		/// @brief Body parameters and statistics
        BodyInfo m_infos;

		/// @brief Body organs
        std::unordered_map<OrganID, Organ::Ptr> m_organs;

		/// @brief Body mouth
		Mouth m_mouth;

		/// @brief Body texture
        sf::Sprite m_sprite;

		/// @brief HUD text
        sf::Text m_bpmHeartText;
        sf::Text m_bpmLungsText;
        sf::Text m_oxygenLevelText;
        sf::Text m_energyLevelText;
		sf::Text m_excrementLevelText;
		sf::Text m_happinessLevelText;
    };
}